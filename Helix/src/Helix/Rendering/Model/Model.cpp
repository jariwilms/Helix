#include "stdafx.hpp"
#include "Model.hpp"

namespace hlx
{
	Model::Model(const std::vector<std::pair<std::shared_ptr<Material>, std::vector<Mesh>>>& meshMap)
		: m_meshMap{ meshMap }, m_materialMeshSizes{}
	{
		createBuffers();
	}
	Model::Model(std::vector<std::pair<std::shared_ptr<Material>, std::vector<Mesh>>>&& meshMap)
		: m_meshMap{ meshMap }, m_materialMeshSizes{}
	{
		createBuffers();
	}

	void Model::createBuffers()
	{
		std::vector<MeshVertex> vertices{};
		std::vector<unsigned int> indices{};
		
		unsigned int meshIndexOffset{};
		for (const auto& it : m_meshMap)
		{
			unsigned int materialMeshCount{};

			for (const auto& mesh : it.second)
			{
				std::vector<MeshVertex> v = mesh.getVertices();
				std::vector<unsigned int> i = mesh.getIndices();

				for (auto& index : i)
					index += meshIndexOffset;

				vertices.insert(vertices.end(), v.begin(), v.end());
				indices.insert(indices.end(), i.begin(), i.end());

				materialMeshCount += static_cast<unsigned int>(i.size());
				meshIndexOffset += static_cast<unsigned int>(v.size());
			}

			m_materialMeshSizes.push_back(materialMeshCount);
		}

		BufferLayout layout{}; //TODO: zonder af naar RenderData ofzo
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(2);
		layout.addAttribute<float>(1);

		auto size = sizeof(MeshVertex) / sizeof(float);

		m_vertexArray = VertexArray<MeshVertex>::create();
		m_vertexBuffer = VertexBuffer<MeshVertex>::create(static_cast<unsigned int>(vertices.size()), (const float*)vertices.data());
		m_elementBuffer = ElementBuffer::create(static_cast<unsigned int>(indices.size()), indices.data());

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->setElementBuffer(m_elementBuffer);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);
	}
}
