#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Vertex.hpp"

namespace hlx
{
	class Mesh
	{
	public:
		virtual ~Mesh() = default;

		static std::shared_ptr<Mesh> create();

		inline std::vector<Vertex>& getVertices() { return m_vertices; }
		inline std::vector<unsigned int>& getIndices() { return m_indices; }
		inline std::vector<std::shared_ptr<Texture>> getTextures() { return m_textures; }

	protected:
		Mesh() = default;

		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};
}
