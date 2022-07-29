#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26495 26451)
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#pragma warning(default: 26495 26451)

#include "Helix/Rendering/Model/Model.hpp"

namespace hlx
{
	class ModelImporter
	{
	public:
		ModelImporter() = default;
		~ModelImporter() = default;

		std::shared_ptr<Model> loadModel(const std::filesystem::path& path, const int flags = 0);

	private:
		glm::mat4 getAbsoluteNodeTransform(const aiNode* node);
		std::vector<MeshVertex> getVertices(const aiMesh* mesh, const glm::mat4& transform);
		std::vector<unsigned int> getIndices(const aiMesh* mesh);
		
		std::shared_ptr<Material> createMaterial(const aiScene* scene, const aiMaterial* aiMaterial, const std::filesystem::path directory);

		std::unique_ptr<Assimp::Importer> m_importer = std::make_unique<Assimp::Importer>();
	};
}
