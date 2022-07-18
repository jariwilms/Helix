#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Model/Mesh.hpp"

namespace hlx
{
	class Model
	{
	public:
		Model(const std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>>& meshMap);
		Model(std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>>&& meshMap);
		virtual ~Model() = default;

		inline const std::shared_ptr<VertexArray<MeshVertex>>& getVertexArray() const { return m_vertexArray; }
		inline const auto& getMeshMap() const { return m_meshMap; }
		inline const auto& getMeshSizes() const { return m_materialMeshSizes; }

	protected:
		void createBuffers();

		std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>> m_meshMap;
		std::vector<unsigned int> m_materialMeshSizes;

		std::shared_ptr<VertexArray<MeshVertex>> m_vertexArray;
		std::shared_ptr<VertexBuffer<MeshVertex>> m_vertexBuffer;
		std::shared_ptr<ElementBuffer> m_elementBuffer;
	};
}
