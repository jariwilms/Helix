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
		Mesh(const std::shared_ptr<Material> material, const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices)
			: m_material{ material }, m_vertices{ vertices }, m_indices{ indices }, m_visible{ true } {}
		virtual ~Mesh() = default;
		
		inline void setVisible(bool state) { m_visible = state; }
		inline bool isVisible() const { return m_visible; }

		inline const std::shared_ptr<Material> getMaterial() const { return m_material; }
		inline const std::vector<MeshVertex>& getVertices() const { return m_vertices; }
		inline const std::vector<unsigned int>& getIndices() const { return m_indices; }

		inline void setMaterial(const std::shared_ptr<Material> material) { m_material = material; } //remove?

	protected:
		std::shared_ptr<Material> m_material;

		std::vector<MeshVertex> m_vertices;
		std::vector<unsigned int> m_indices;

		bool m_visible;
	};
}
