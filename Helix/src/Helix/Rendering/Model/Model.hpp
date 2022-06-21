#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx
{
	class Model
	{
	public:
		virtual ~Model() = default;

		static std::shared_ptr<Model> create(std::filesystem::path path);
		static std::shared_ptr<Model> create();

		inline std::vector<Mesh>& getMeshes() { return m_meshes; }

	protected:
		Model() = default;

		std::vector<Mesh> m_meshes;
	};
}
