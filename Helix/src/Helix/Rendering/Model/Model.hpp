#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Model/Mesh.hpp"

namespace hlx
{
	class Model
	{
	public:
		Model(std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>> materialToMeshMap);
		virtual ~Model() = default;

		inline const std::shared_ptr<VertexArray>& getVertexArray() const { return m_vertexArray; }
		inline const std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>>& getMeshes() const { return m_materialToMeshMap; }

	protected:
		std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>> m_materialToMeshMap;

		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<ElementBuffer> m_elementBuffer;
	};
}
