#include "stdafx.hpp"
#include "Model.hpp"

namespace hlx
{
	Model::Model(const std::vector<Mesh>& meshes)
	{
		m_meshes = meshes;

		createBuffers();
	}
	Model::Model(std::vector<Mesh>&& meshes)
	{
		m_meshes = std::move(meshes);

		createBuffers();
	}

	void Model::createBuffers()
	{
		std::vector<MeshVertex> vertices{};
		std::vector<unsigned int> indices{};

		for (const auto& mesh : m_meshes)
		{
			std::vector<MeshVertex> v = mesh.getVertices();
			std::vector<unsigned int> i = mesh.getIndices();

			vertices.insert(vertices.end(), v.begin(), v.end());
			indices.insert(indices.end(), i.begin(), i.end());
		}

		BufferLayout layout{}; //TODO: zonder af naar RenderData ofzo
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(2);
		layout.addAttribute<float>(1);

		auto size = sizeof(MeshVertex) / sizeof(float);

		m_vertexArray = VertexArray::create();
		m_vertexBuffer = VertexBuffer::create(static_cast<unsigned int>(vertices.size() * size), (const float*)vertices.data());
		m_elementBuffer = ElementBuffer::create(static_cast<unsigned int>(indices.size()), indices.data());

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->setElementBuffer(m_elementBuffer);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);
	}
}
