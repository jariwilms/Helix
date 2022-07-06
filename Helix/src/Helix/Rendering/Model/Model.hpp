#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Model/Mesh.hpp"

namespace hlx
{
	class Model
	{
	public:
		Model(const std::vector<Mesh>& meshes);
		Model(std::vector<Mesh>&& meshes);
		virtual ~Model() = default;

		inline const std::shared_ptr<VertexArray>& getVertexArray() const { return m_vertexArray; }
		inline const std::vector<Mesh>& getMeshes() const { return m_meshes; }

	protected:
		void createBuffers();

		std::vector<Mesh> m_meshes;

		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<ElementBuffer> m_elementBuffer;
	};
}
