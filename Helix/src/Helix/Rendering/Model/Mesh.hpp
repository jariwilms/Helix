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
		Mesh(std::shared_ptr<VertexArray> vertexArray)
			: m_vertexArray{ vertexArray }
		{
			auto shader = Shader::create("shaders/material.vert", "shaders/material.frag");
			m_material = std::make_shared<Material>(shader);
		}
		virtual ~Mesh() = default;

		inline std::shared_ptr<VertexArray> getVertexArray() const { return m_vertexArray; }
		inline std::shared_ptr<Material> getMaterial() const { return m_material; }

		inline void setMaterial(std::shared_ptr<Material> material) { m_material = material; }

	protected:
		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<Material> m_material;
	};
}
