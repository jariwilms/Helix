#include "stdafx.hpp"
#include "ModelImporter.hpp"

#include "Helix/IO/IO.hpp"

namespace hlx
{
	std::shared_ptr<Model> ModelImporter::loadModel(const std::filesystem::path& path, const int flags)
	{
		auto directory = path.parent_path();
		auto scene = m_importer->ReadFile(path.string(), flags);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			HLX_CORE_ERROR("Failed to load model: {0}", m_importer->GetErrorString());
			return nullptr;
		}



		std::stack<aiNode*> nodeStack{};
		nodeStack.push(scene->mRootNode);

		std::vector<std::pair<std::shared_ptr<Material>, std::vector<Mesh>>> meshMap;


		
		for (unsigned int i{}; i < scene->mNumMaterials; ++i)
			meshMap.emplace_back(createMaterial(scene, scene->mMaterials[i], directory), std::vector<Mesh>{});



		//Iterate over children of root node (DFS)
		while (!nodeStack.empty())
		{
			auto node = nodeStack.top();
			nodeStack.pop();

			auto transform = getAbsoluteNodeTransform(node);



			//Iterate over node meshes
			for (unsigned int i{}; i < node->mNumMeshes; ++i)
			{
				auto aiMesh = scene->mMeshes[node->mMeshes[i]];

				std::vector<MeshVertex> vertices;
				std::vector<unsigned int> indices;



				auto verts = getVertices(aiMesh, transform);
				if (!verts.empty())
				{
					vertices.reserve(vertices.size() + verts.size());
					std::move(std::begin(verts), std::end(verts), std::back_inserter(vertices));
					verts.clear();
				}

				auto inds = getIndices(aiMesh);
				if (!inds.empty())
				{
					indices.reserve(indices.size() + inds.size());
					std::move(std::begin(inds), std::end(inds), std::back_inserter(indices));
					inds.clear();
				}



				auto& meshes = meshMap.at(aiMesh->mMaterialIndex).second;
				meshes.emplace_back(std::move(vertices), std::move(indices));
			}

			//Push children of current node on top of stack
			for (unsigned int i{}; i < node->mNumChildren; ++i)
				nodeStack.push(node->mChildren[i]);
		}


		
		return std::make_shared<Model>(std::move(meshMap));
	}

	std::vector<MeshVertex> ModelImporter::getVertices(const aiMesh* mesh, const glm::mat4& transform)
	{
		std::vector<MeshVertex> vertices{};

		for (unsigned int i{}; i < mesh->mNumVertices; ++i)
		{
			MeshVertex vertex{};
			std::memcpy(&vertex.position, &mesh->mVertices[i], sizeof(glm::vec3));
			if (mesh->HasTextureCoords(0)) std::memcpy(&vertex.textureCoordinate, &mesh->mTextureCoords[0][i], sizeof(glm::vec2));
			if (mesh->HasNormals()) std::memcpy(&vertex.normal, &mesh->mNormals[i], sizeof(glm::vec3));
			if (mesh->HasTangentsAndBitangents())
			{
				std::memcpy(&vertex.tangent, &mesh->mTangents[i], sizeof(glm::vec3));
				std::memcpy(&vertex.bitangent, &mesh->mBitangents[i], sizeof(glm::vec3));
			}

			glm::vec4 pos = glm::vec4{ vertex.position, 1.0f };
			pos = transform * pos;
			vertex.position = pos;

			vertices.push_back(vertex);
		}

		return vertices;
	}
	std::vector<unsigned int> ModelImporter::getIndices(const aiMesh* mesh)
	{
		std::vector<unsigned int> indices{};

		for (unsigned int i{}; i < mesh->mNumFaces; ++i)
		{
			auto& face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; ++j)
				indices.push_back(face.mIndices[j]);
		}

		return indices;
	}

	std::shared_ptr<Material> ModelImporter::createMaterial(const aiScene* scene, const aiMaterial* material, const std::filesystem::path directory) //TODO: move dir to private var => CWD ofzo
	{
		using setTextureFunc = void (hlx::Material::*)(std::shared_ptr<Texture> texture);
		const std::vector<aiTextureType> textureTypes{ aiTextureType_DIFFUSE, aiTextureType_NORMALS, aiTextureType_SPECULAR }; //TODO: extend
		const std::unordered_map<int, setTextureFunc> textureFuncs
		{
			{std::make_pair(aiTextureType_DIFFUSE, &Material::setAlbedo)},
			{std::make_pair(aiTextureType_NORMALS, &Material::setNormal)},
			{std::make_pair(aiTextureType_SPECULAR, &Material::setSpecular)},
		};
		

		
		aiString materialName;
		aiReturn success;

		success = material->Get(AI_MATKEY_NAME, materialName);
		if (success != AI_SUCCESS) materialName = "Default";

		auto shader = Shader::create("shaders/material2.glsl");
		auto mat = std::make_shared<Material>(materialName.C_Str(), shader);
		


		for (const auto textureType : textureTypes)
		{
			const int count = material->GetTextureCount(textureType);
			if (!count) continue;

			aiString textureName;
			success = material->Get(AI_MATKEY_TEXTURE(textureType, 0), textureName);

			if (success != AI_SUCCESS) continue;

			

			const aiTexture* embeddedTexture = scene->GetEmbeddedTexture(textureName.C_Str());
			if (embeddedTexture) //Texture is embedded in file -> load from memory
			{
				//auto texture = stbi_load_from_memory()
			}
			else //Texture is not embedded -> load from disk
			{
				auto texture = IO::load<Texture>(directory / textureName.C_Str());
				std::invoke(textureFuncs.find(textureType)->second, mat, texture);
			}
		}

		return mat;
	}
	std::shared_ptr<Texture> ModelImporter::loadTextureEmbedded(const aiTexture* aiTexture)
	{
		auto width = aiTexture->mWidth;
		auto height = aiTexture->mHeight;
		auto aiTexel = aiTexture->pcData;

		auto data = convertToRGBA(aiTexture);

		TextureBlueprint blueprint{ TextureType::Texture2D, glm::uvec2{width, height} };
		return Texture::create(blueprint, data);
	}
	std::shared_ptr<Texture> ModelImporter::loadTextureFile(const std::filesystem::path& filePath)
	{
		return IO::load<Texture>(filePath);
	}
	
	glm::mat4 ModelImporter::getAbsoluteNodeTransform(const aiNode* node)
	{
		std::vector<const aiNode*> nodes = { node };
		glm::mat4 compoundTransform{ 1.0f };

		while (nodes.back()->mParent)
		{
			auto node = nodes.back();
			nodes.push_back(node->mParent);
		}

		for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
		{
			auto node = *it;

			if (node->mTransformation.IsIdentity()) continue;
			compoundTransform = compoundTransform * glm::transpose(glm::make_mat4(&node->mTransformation.a1));
		}

		return compoundTransform;
	}
	const unsigned char* ModelImporter::convertToRGBA(const aiTexture* aiTexture)
	{
		auto totalBytes = 4 * aiTexture->mWidth * aiTexture->mHeight;

		auto* iData = (unsigned char*)aiTexture->pcData;
		auto* oData = new unsigned char[totalBytes];

		unsigned int counter = 0;

		//iterate width => height so cpu cache doesn't explode
		for (unsigned int i{}; i < totalBytes - 4; i += 4)
		{
			oData[i + 0] = iData[i + 1];
			oData[i + 1] = iData[i + 2];
			oData[i + 2] = iData[i + 3];
			oData[i + 3] = iData[i + 0];
		}

		return oData;
	}
}
