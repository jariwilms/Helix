#include "stdafx.hpp"
#include "OpenGLRenderer.hpp"

namespace hlx
{
	OpenGLRenderer::OpenGLRenderer()
	{
		constexpr size_t MAX_INDICES = (size_t)1 << 15; //TODO: move naar renderdata / rendersettings?
		constexpr size_t BUFFER_SIZE = MAX_INDICES * sizeof(Vertex);

		BufferLayout layout{};
		layout.addAttribute<float>(3); //position
		layout.addAttribute<float>(4); //color
		layout.addAttribute<float>(2); //texture coordinate
		layout.addAttribute<float>(1); //texture index
		layout.addAttribute<float>(1); //tiling factor
		layout.addAttribute<float>(1); //entity id

		m_renderBatch = std::make_shared<RenderBatch>(BUFFER_SIZE, MAX_INDICES, layout);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRenderer::start(const Camera& camera)
	{
		m_view = camera.getViewMatrix();
		m_projection = camera.getProjectionMatrix();

		m_statistics.reset();
	}
	void OpenGLRenderer::check()
	{
		if (m_renderBatch->textureCount == 32) submit();
	}
	void OpenGLRenderer::submit()
	{
		if (!m_renderBatch->vertexCount || !m_renderBatch->elementCount)
			return;

		m_renderBatch->bind();
		m_renderBatch->vbo->setBufferData(m_renderBatch->vertexCount * sizeof(Vertex), (float*)m_renderBatch->vertexPtr);
		m_renderBatch->ebo->setBufferData(m_renderBatch->elementCount * sizeof(unsigned int), m_renderBatch->elementPtr);

		m_renderBatch->shader->setMat("u_view", m_view);
		m_renderBatch->shader->setMat("u_projection", m_projection);

		glDrawElements(GL_TRIANGLES, (GLsizei)m_renderBatch->elementCount, GL_UNSIGNED_INT, nullptr);

		++m_statistics.drawCalls;

		m_renderBatch->reset();
	}
	void OpenGLRenderer::finish()
	{
		submit();
	}

	void OpenGLRenderer::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void OpenGLRenderer::clearBackground(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}



	void OpenGLRenderer::renderQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
	{
		glm::mat4 transform{ 1.0f };
		transform *= glm::translate(glm::mat4{ 1.0f }, position);
		transform *= glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale, 0.0f });

		renderQuad(transform, color);
	}
	void OpenGLRenderer::renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint)
	{
		glm::mat4 transform{ 1.0f };
		transform *= glm::translate(glm::mat4{ 1.0f }, position);
		transform *= glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale, 0.0f });

		renderQuad(transform, texture, textureScale, textureTint);
	}

	void OpenGLRenderer::renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		glm::mat4 transform{ 1.0f };
		transform *= glm::translate(glm::mat4{ 1.0f }, position);
		transform *= glm::rotate(glm::mat4{ 1.0f }, glm::radians(rotation), glm::vec3{ 0.0f, 0.0f, 1.0f });
		transform *= glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale, 0.0f });

		renderQuad(transform, color);
	}
	void OpenGLRenderer::renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint)
	{
		glm::mat4 transform{ 1.0f };
		transform *= glm::translate(glm::mat4{ 1.0f }, position);
		transform *= glm::rotate(glm::mat4{ 1.0f }, glm::radians(rotation), glm::vec3{ 0.0f, 0.0f, 1.0f });
		transform *= glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale, 0.0f });

		renderQuad(transform, texture, textureScale, textureTint);
	}

	void OpenGLRenderer::renderQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		for (int i = 0; i < RenderData::QUAD_VERTICES; ++i)
		{
			auto& vertex = m_renderBatch->vertexPtr[m_renderBatch->vertexCount];

			vertex.position = transform * glm::vec4{ RenderData::QUAD_VERTEX_POSITIONS[i], 1.0f };
			vertex.color = color;
			vertex.textureCoordinate = RenderData::QUAD_TEXTURE_COORDINATES[i];
			vertex.textureIndex = 0.0f;
			vertex.textureScale = 1.0f;
			vertex.entityId = 0;

			++m_renderBatch->vertexCount;
		}

		m_renderBatch->elementCount += 6;

		m_statistics.vertices += 4;
		m_statistics.triangles += 2;

		check();
	}
	void OpenGLRenderer::renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint)
	{
		if (texture == nullptr) return;

		constexpr auto vertices = RenderData::QUAD_VERTICES;

		for (int i = 0; i < vertices; ++i)
		{
			auto& vertex = m_renderBatch->vertexPtr[m_renderBatch->vertexCount];

			vertex.position = transform * glm::vec4{ RenderData::QUAD_VERTEX_POSITIONS[i], 1.0f };
			vertex.color = textureTint;
			vertex.textureCoordinate = RenderData::QUAD_TEXTURE_COORDINATES[i];
			vertex.textureIndex = (float)m_renderBatch->textureCount;
			vertex.textureScale = textureScale;
			vertex.entityId = 0;

			++m_renderBatch->vertexCount;
		}

		m_renderBatch->elementCount += 6;

		m_renderBatch->textureSlots[m_renderBatch->textureCount] = texture;
		++m_renderBatch->textureCount;

		m_statistics.vertices += 4;
		m_statistics.triangles += 2;

		check();
	}



	void OpenGLRenderer::renderModel(Model& model, const glm::mat4& transform)
	{
		auto& meshes = model.getMeshes();

		for (const auto& mesh : meshes)
		{
			auto& vao = mesh.getVertexArray();
			auto material = mesh.getMaterial();
			auto& shader = material->getShader();

			vao->bind();
			material->bind();
			shader->setMat("u_model", transform);
			shader->setMat("u_view", m_view);
			shader->setMat("u_projection", m_projection);

			glDrawElements(GL_TRIANGLES, (GLsizei)vao->getElementBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);
		}
	}



	void OpenGLRenderer::poll()
	{
		m_statistics.reset();
	}
	RenderStatistics OpenGLRenderer::measure()
	{
		m_statistics.measure();
		return m_statistics;
	}
}
