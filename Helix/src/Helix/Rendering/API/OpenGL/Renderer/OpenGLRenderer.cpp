#include "stdafx.hpp"
#include "OpenGLRenderer.hpp"

namespace hlx
{
	OpenGLRenderer::OpenGLRenderer()
		: m_vertexIndex{}, m_elementIndex{}
	{
		constexpr size_t MAX_VERTICES = (size_t)1 << 15;
		constexpr size_t BUFFER_SIZE = MAX_VERTICES * sizeof(Vertex);



		BufferLayout layout{};
		layout.addAttribute<float>(3); //position
		layout.addAttribute<float>(4); //color
		layout.addAttribute<float>(2); //texture coordinate
		layout.addAttribute<float>(1); //texture index
		layout.addAttribute<float>(1); //tiling factor
		layout.addAttribute<float>(1); //entity id

		m_vao = VertexArray::create();
		m_vbo = VertexBuffer::create(BUFFER_SIZE);
		m_ebo = ElementBuffer::create(MAX_VERTICES);

		m_vbo->setLayout(layout);
		m_vao->setElementBuffer(m_ebo);
		m_vao->addVertexBuffer(m_vbo);



		m_vertices = new Vertex[BUFFER_SIZE];
		m_elements = new unsigned int[MAX_VERTICES];



		m_shader = Shader::create("Shaders/test.vert", "Shaders/test.frag");
	}

	void OpenGLRenderer::start(const Camera& camera)
	{
		m_camera = camera;
	}

	void OpenGLRenderer::submit()
	{
		if (!m_vertexIndex || !m_elementIndex)
			return;

		m_shader->bind();
		m_shader->setMat("u_projection", m_camera.getProjectionMatrix());
		m_shader->setMat("u_view", m_camera.getViewMatrix());

		m_vbo->setBufferData(m_vertexIndex * sizeof(Vertex), (float*)m_vertices);
		m_ebo->setBufferData(m_elementIndex * sizeof(unsigned int), m_elements);
		m_vao->bind();

		glDrawElements(GL_TRIANGLES, (GLsizei)m_elementIndex, GL_UNSIGNED_INT, nullptr);

		m_vertexIndex = 0;
		m_elementIndex = 0;
	}

	void OpenGLRenderer::finish()
	{

	}

	void OpenGLRenderer::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer::clearBackground(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderer::renderQuad(const glm::vec3& position)
	{
		constexpr size_t vertices = 4;
		constexpr float texIndex = 0;
		constexpr float texTiling = 0;
		constexpr glm::vec3 vertexPositions[] = { { -0.5f, 0.5f, 0.0f }, { -0.5f, -0.5f, 0.0f }, { 0.5f, -0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f } };
		constexpr glm::vec2 texCoords[] = { { 0.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f } };

		for (int i = 0; i < vertices; ++i)
		{
			auto& vertex = m_vertices[m_vertexIndex];

			vertex.position = vertexPositions[i];
			vertex.color = glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f };
			vertex.textureCoordinate = texCoords[i];
			vertex.textureIndex = 0;
			vertex.tilingFactor = 1.0f;
			vertex.entityId = 0;

			++m_vertexIndex;
		}

		m_elements[m_elementIndex + 0] = 0;
		m_elements[m_elementIndex + 1] = 1;
		m_elements[m_elementIndex + 2] = 2;

		m_elements[m_elementIndex + 3] = 0;
		m_elements[m_elementIndex + 4] = 2;
		m_elements[m_elementIndex + 5] = 3;

		m_elementIndex += 6;
	}
}
