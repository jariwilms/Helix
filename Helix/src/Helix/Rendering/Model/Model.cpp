#include "stdafx.hpp"
#include "Model.hpp"

namespace hlx
{
	Model::Model(std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh>> materialToMeshMap)
	{
		m_materialToMeshMap = materialToMeshMap;
		
		std::vector<MeshVertex> vertices{};
		std::vector<unsigned int> indices{};

		for (const auto& it : m_materialToMeshMap)
		{
			for (const auto& mesh : it.second)
			{
				std::vector<MeshVertex> v = mesh.getVertices();
				std::vector<unsigned int> i = mesh.getIndices();

				vertices.insert(vertices.end(), v.begin(), v.end());
				indices.insert(indices.end(), i.begin(), i.end());
			}
		}


		
		BufferLayout layout{};
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
