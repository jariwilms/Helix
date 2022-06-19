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

	protected:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		{

		}

		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<Texture> m_textures;
	};
}
