#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Model/Mesh.hpp"

namespace hlx
{
	class Model
	{
	public:
		Model() = default;
		virtual ~Model() = default;

		inline std::vector<Mesh>& getMeshes() { return m_meshes; }

	protected:
		std::vector<Mesh> m_meshes;
	};
}
