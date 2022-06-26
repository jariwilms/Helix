#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26495)
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#pragma warning(default: 26495)

#pragma warning(disable: 26819 6262 26451)
#include "stb/stb_image.h"
#pragma warning(default: 26819 6262 26451)

#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Model/Mesh.hpp"
#include "Helix/Rendering/Model/Model.hpp"

namespace hlx
{
	class IO
	{
	public:
		class Affix
		{
		public:
			Affix(const std::filesystem::path relativePath)
			{
				HLX_CORE_INFO("Appended \"{0}\" to current path", relativePath.string().c_str());
				IO::m_subdirectories.push_back(relativePath);
			}
			~Affix()
			{
				auto& relativePath = m_subdirectories.at(m_subdirectories.size() - 1);
				HLX_CORE_INFO("Detached \"{0}\" from current path", relativePath.string().c_str());
				IO::m_subdirectories.pop_back();
			}
		};

		static void init()
		{
			m_root = std::filesystem::current_path().parent_path().lexically_normal();
			HLX_CORE_INFO("HLX::IO::INIT");
			HLX_CORE_INFO("Setting root path to {0}", m_root.string().c_str());
		}

		inline static bool checkFileExists(const std::filesystem::path& path) { return std::filesystem::exists(path);  }
		inline static bool checkDirectoryExists(const std::filesystem::path& path) { return std::filesystem::exists(path); }

		inline static const std::filesystem::path& getRoot() { return m_root; }
		inline static void setRoot(const std::filesystem::path& root) { m_root = root; }

		inline static std::filesystem::path getCurrentWorkingDirectory() { return std::filesystem::current_path(); }
		inline static std::filesystem::path getCoalescedPath(std::filesystem::path path = "")
		{
			std::filesystem::path coalesced = m_root;
			std::for_each(m_subdirectories.begin(), m_subdirectories.end(), [&](const std::filesystem::path& _) { coalesced /= _; });

			return (coalesced / path).lexically_normal();
		}

		template<typename T, typename... Args>
		inline static std::shared_ptr<T> load(const std::filesystem::path& path, Args... args)
		{
			HLX_CORE_ASSERT(false, "Invalid file format");
		}
		template<> inline static std::shared_ptr<std::string> load<std::string>(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath;

			if (path.is_absolute()) fullPath = path;
			else fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return nullptr;
			}
			if (m_textFiles.find(fullPath) != m_textFiles.end()) return m_textFiles[fullPath];



			std::ifstream file(fullPath);
			auto result = std::make_shared<std::string>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			m_textFiles.insert(std::make_pair(fullPath, result));
			file.close();

			return m_textFiles[fullPath];
		}
		template<> inline static std::shared_ptr<Texture> load<Texture>(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath;

			if (path.is_absolute()) fullPath = path;
			else fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return load<Texture>("textures/missing.png");
			}
			if (m_textures.find(fullPath) != m_textures.end()) return m_textures[fullPath];



			int width, height, channels;
			unsigned char* data;

			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(fullPath.string().c_str(), &width, &height, &channels, 0);
			if (!data) return load<Texture>("textures/missing.png");

			auto texture = Texture::create(width, height, channels, data);
			m_textures.insert(std::make_pair(fullPath, texture));

			return texture;
		}
		template<> inline static std::shared_ptr<Model> load<Model>(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath{};
			std::filesystem::path directory{};

			if (path.is_absolute()) fullPath = path;
			else fullPath = getCoalescedPath(path);
			if (fullPath.has_parent_path()) directory = fullPath.parent_path();

			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return nullptr;
			}
			if (m_textFiles.find(fullPath) != m_textFiles.end()) return m_models[fullPath];



			Assimp::Importer importer;
			auto scene = importer.ReadFile(fullPath.string(), aiProcess_Triangulate);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				HLX_CORE_ERROR("Failed to load model: {0}", importer.GetErrorString());
				return nullptr;
			}



			auto model = std::make_shared<Model>();
			auto& meshes = model->getMeshes();

			std::stack<aiNode*> nodeStack{};
			nodeStack.push(scene->mRootNode);

			while (!nodeStack.empty())
			{
				auto node = nodeStack.top();
				nodeStack.pop();

				for (unsigned int i{ 0 }; i < node->mNumChildren; ++i)
					nodeStack.push(node->mChildren[i]);

				for (unsigned int i{ 0 }; i < node->mNumMeshes; ++i)
				{
					auto aiMesh = scene->mMeshes[node->mMeshes[i]];

					std::vector<MeshVertex> vertices;
					std::vector<unsigned int> indices;

					for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
					{
						MeshVertex vertex{};

						std::memcpy(&vertex.position, &aiMesh->mVertices[i], sizeof(glm::vec3));
						if (aiMesh->HasNormals()) std::memcpy(&vertex.normal, &aiMesh->mNormals[i], sizeof(glm::vec3));

						if (aiMesh->mTextureCoords) std::memcpy(&vertex.textureCoordinate, &aiMesh->mTextureCoords[0][i], sizeof(glm::vec2));
						else vertex.textureCoordinate = glm::vec2(0.0f, 0.0f);

						if (aiMesh->mTangents) std::memcpy(&vertex.tangent, &aiMesh->mTangents[i], sizeof(glm::vec3));
						if (aiMesh->mBitangents) std::memcpy(&vertex.bitangent, &aiMesh->mBitangents[i], sizeof(glm::vec3));

						vertices.push_back(vertex);
					}

					for (unsigned int i = 0; i < aiMesh->mNumFaces; ++i)
					{
						auto& face = aiMesh->mFaces[i];

						for (unsigned int j = 0; j < face.mNumIndices; ++j)
							indices.push_back(face.mIndices[j]);
					}

					BufferLayout layout{};
					layout.addAttribute<float>(3);
					layout.addAttribute<float>(3);
					layout.addAttribute<float>(3);
					layout.addAttribute<float>(3);
					layout.addAttribute<float>(2);
					layout.addAttribute<float>(1);

					auto vertexArray = VertexArray::create();
					auto vertexBuffer = VertexBuffer::create(vertices.size() * sizeof(MeshVertex), (float*)vertices.data());
					auto elementBuffer = ElementBuffer::create(indices.size() * sizeof(unsigned int), indices.data());

					vertexBuffer->setLayout(layout);
					vertexArray->setElementBuffer(elementBuffer);
					vertexArray->addVertexBuffer(vertexBuffer);

					auto& mesh = meshes.emplace_back(vertexArray);
					auto meshMaterial = mesh.getMaterial();
					auto material = scene->mMaterials[aiMesh->mMaterialIndex];


					mesh.setMaterial(createMaterial(material));
				}
			}

			m_models.insert(std::make_pair(fullPath, model));
			return model;
		}

	private:
		static bool hasTextureType(aiMaterial* material, aiTextureType type)
		{
			return material->GetTextureCount(type);
		}
		static std::string getTextureName(aiMaterial * material, aiTextureType type)
		{
				aiString textureName{};
				material->GetTexture(type, 0, &textureName);
				return "models/" + std::string{textureName.C_Str()}; //dit is echt scuffed
		}
		static std::shared_ptr<Material> createMaterial(aiMaterial* aiMaterial)
		{
			auto shader = Shader::create("shaders/material.vert", "shaders/material.frag");
			auto meshMaterial = std::make_shared<Material>(shader);

			if (hasTextureType(aiMaterial, aiTextureType_DIFFUSE))
			{
				std::string name = getTextureName(aiMaterial, aiTextureType_DIFFUSE);
				meshMaterial->setAlbedo(load<Texture>(name));
			}

			if (hasTextureType(aiMaterial, aiTextureType_NORMALS))
			{
				std::string name = getTextureName(aiMaterial, aiTextureType_NORMALS);
				meshMaterial->setNormal(load<Texture>(name));
			}

			if (hasTextureType(aiMaterial, aiTextureType_SPECULAR))
			{
				std::string name = getTextureName(aiMaterial, aiTextureType_SPECULAR);
				meshMaterial->setSpecular(load<Texture>(name));
			}

			return meshMaterial;
		}


		static void logError(std::filesystem::path path)
		{
			const std::string filename = path.filename().string();
			const std::string parent = path.remove_filename().generic_string();
			HLX_CORE_WARNING("File \"{0}\" was not found at location \"{1}\"", filename, parent);
		}

		inline static std::filesystem::path m_root;
		inline static std::vector<std::filesystem::path> m_subdirectories;

		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<std::string>> m_textFiles;
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Model>> m_models;
	};
}
