#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Model/Material.hpp"
#include "Helix/Rendering/Object/VertexArray.hpp"
#include "Helix/Rendering/Object/VertexBuffer.hpp"
#include "Helix/Rendering/Object/ElementBuffer.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Data/MeshVertex.hpp"

namespace hlx
{
	class Mesh
	{
	public:
		Mesh(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices)
			: m_vertices{ vertices }, m_indices{ indices } {}
		Mesh(std::vector<MeshVertex>&& vertices, std::vector<unsigned int>&& indices)
			: m_vertices{ vertices }, m_indices{ indices } {}
		virtual ~Mesh() = default;

		inline const std::vector<MeshVertex>& getVertices() const { return m_vertices; }
		inline const std::vector<unsigned int>& getIndices() const { return m_indices; }

	protected:
		std::vector<MeshVertex> m_vertices;
		std::vector<unsigned int> m_indices;
	};
}
