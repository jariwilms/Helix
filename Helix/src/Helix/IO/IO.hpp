#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26495 26451)
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#pragma warning(default: 26495 26451)

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
		template<> inline static std::shared_ptr<Shader> load(const std::filesystem::path& path)
		{
			std::filesystem::path fullPath;

			if (path.is_absolute()) fullPath = path;
			else fullPath = getCoalescedPath(path);

			if (!checkFileExists(fullPath))
			{
				logError(fullPath);
				return nullptr;
			}
			if (m_shaders.find(fullPath) != m_shaders.end()) return m_shaders[fullPath];

			
			
			const std::string vertexDelimiter = "@vertex\n";
			const std::string geometryDelimiter = "@geometry\n";
			const std::string fragmentDelimiter = "@fragment\n";

			auto content = load<std::string>(fullPath);
			auto vertexPosition = content->find(vertexDelimiter);
			auto geometryPosition = content->find(geometryDelimiter);
			auto fragmentPosition = content->find(fragmentDelimiter);

			
			
			std::string vertex = content->substr(vertexPosition, fragmentPosition);
			std::string fragment = content->substr(fragmentPosition, std::string::npos);
			
			vertex.erase(0, vertexDelimiter.length());
			fragment.erase(0, fragmentDelimiter.length());


			
			auto shader = Shader::create(vertex, fragment);
			m_shaders.insert(std::make_pair(fullPath, shader));
			
			return shader;

			// "AI will kill us"
			// AI:
			//if (position == std::string::npos)
			//{
			//	vertex = content->substr(0, position);
			//	fragment = content->substr(position + 9);
			//}
			//else
			//{
			//	vertex = content->substr(0, position);
			//	fragment = content->substr(position + 9);
			//}
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
			data = stbi_load(fullPath.string().c_str(), &width, & height, &channels, 0);
			if (!data)
			{
				logError(fullPath);
				return load<Texture>("textures/missing.png");
			}

			auto texture = Texture::create({ width, height }, channels, data);
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
			if (m_models.find(fullPath) != m_models.end()) return m_models[fullPath];



			Assimp::Importer importer;
			constexpr auto importerFlags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;// | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph;
			auto scene = importer.ReadFile(fullPath.string(), importerFlags);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				HLX_CORE_ERROR("Failed to load model: {0}", importer.GetErrorString());
				return nullptr;
			}


			
			std::stack<aiNode*> nodeStack{};
			nodeStack.push(scene->mRootNode);

			std::unordered_map<unsigned int, std::shared_ptr<Material>> idToMaterialMap;
			std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>> materialToMeshMap{};
			
			unsigned int offset{};

			//Iterate over children of root node (DFS)
			while (!nodeStack.empty())
			{
				auto node = nodeStack.top();
				nodeStack.pop();

				for (unsigned int i{ 0 }; i < node->mNumMeshes; ++i)
				{
					auto aiMesh = scene->mMeshes[node->mMeshes[i]];

					std::vector<MeshVertex> vertices;
					std::vector<unsigned int> indices;

					//Iterate over mesh vertices and set the correct data to our own vertex
					for (unsigned int i = 0; i < aiMesh->mNumVertices; ++i)
					{
						MeshVertex vertex{};
						
						std::memcpy(&vertex.position, &aiMesh->mVertices[i], sizeof(glm::vec3));
						if (aiMesh->HasNormals()) std::memcpy(&vertex.normal, &aiMesh->mNormals[i], sizeof(glm::vec3));
						if (aiMesh->HasTangentsAndBitangents())
						{
							std::memcpy(&vertex.tangent, &aiMesh->mTangents[i], sizeof(glm::vec3));
							std::memcpy(&vertex.bitangent, &aiMesh->mBitangents[i], sizeof(glm::vec3));
						}
						
						if (aiMesh->mTextureCoords) std::memcpy(&vertex.textureCoordinate, &aiMesh->mTextureCoords[0][i], sizeof(glm::vec2));

						vertices.push_back(vertex);
					}

					unsigned int c{};
					//Iterate over faces to fetch indices
					for (unsigned int i = 0; i < aiMesh->mNumFaces; ++i)
					{
						auto& aiFace = aiMesh->mFaces[i];
						c += aiFace.mNumIndices;

						for (unsigned int j = 0; j < aiFace.mNumIndices; ++j)
							indices.push_back(aiFace.mIndices[j] + offset);
					}

					offset += c;

					auto materialIndex = aiMesh->mMaterialIndex;
					auto it = idToMaterialMap.find(materialIndex);
					if (it == idToMaterialMap.end())
					{
						auto aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];
						idToMaterialMap.insert(std::make_pair(materialIndex, createMaterial(directory, aiMaterial)));
						it = idToMaterialMap.find(materialIndex);
					}

					auto& mat = it->second;
					auto it2 = materialToMeshMap.find(mat);

					if (it2 == materialToMeshMap.end())
					{
						materialToMeshMap.insert(std::make_pair(mat, std::vector<Mesh>{}));
						it2 = materialToMeshMap.find(mat);
					}

					it2->second.emplace_back(vertices, indices);
				}
				
				for (unsigned int i{ 0 }; i < node->mNumChildren; ++i)
					nodeStack.push(node->mChildren[i]);
			}

			auto model = m_models.insert(std::make_pair(fullPath, std::make_shared<Model>(materialToMeshMap)));
			return model.first->second;
		}

	private:
		static bool hasTextureType(aiMaterial* material, aiTextureType type)
		{
			auto val = material->GetTextureCount(type);
			return val;
		}
		static std::string getTextureName(aiMaterial* material, aiTextureType type)
		{
				aiString textureName{};
				material->GetTexture(type, 0, &textureName);
				return textureName.C_Str();
		}
		static std::shared_ptr<Material> createMaterial(std::filesystem::path directory, aiMaterial* aiMaterial)
		{
			using setTextureFunc = void (hlx::Material::*)(std::shared_ptr<Texture> texture);

			auto shader = Shader::create("shaders/material.glsl");
			auto meshMaterial = std::make_shared<Material>(shader);

			const std::vector<aiTextureType> textureTypes { aiTextureType_DIFFUSE, aiTextureType_NORMALS, aiTextureType_SPECULAR };
			const std::unordered_map<int, setTextureFunc> textureFuncs
			{
				{std::make_pair(aiTextureType_DIFFUSE, &Material::setAlbedo)}, 
				{std::make_pair(aiTextureType_NORMALS, &Material::setNormal)},
				{std::make_pair(aiTextureType_SPECULAR, &Material::setSpecular)},
			};

			for (auto textureType : textureTypes)
			{
				if (!aiMaterial->GetTextureCount(textureType)) continue;

				std::string name = getTextureName(aiMaterial, textureType);
				auto texture = load<Texture>(directory / name);

				std::invoke(textureFuncs.find(textureType)->second, meshMaterial, texture);
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
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Shader>> m_shaders;
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
		inline static std::unordered_map<std::filesystem::path, std::shared_ptr<Model>> m_models;
	};
}
