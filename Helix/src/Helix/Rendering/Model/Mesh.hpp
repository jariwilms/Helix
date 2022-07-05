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
		Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices)
			: m_vertices{vertices}, m_indices{indices}
		{
			m_material = std::make_shared<Material>();
		}
		virtual ~Mesh() = default;
		
		inline void setVisible(bool state) { m_visible = state; }
		inline bool isVisible() const { return m_visible; }

		inline const std::vector<MeshVertex>& getVertices() const { return m_vertices; }
		inline const std::vector<unsigned int>& getIndices() const { return m_indices; }
		inline std::shared_ptr<Material> getMaterial() const { return m_material; }

		inline void setMaterial(std::shared_ptr<Material> material) { m_material = material; } //remove?

	protected:
		std::vector<MeshVertex> m_vertices;
		std::vector<unsigned int> m_indices;
		
		std::shared_ptr<Material> m_material;

		bool m_visible;
	};
}
