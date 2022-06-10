#include "stdafx.hpp"
#include "OpenGLRenderer.hpp"

namespace hlx
{
	OpenGLRenderer::OpenGLRenderer()
		: m_scene{}
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
	}

	void OpenGLRenderer::start(Scene* scene)
	{
		m_scene = scene;

		m_renderBatch->reset();
	}
	void OpenGLRenderer::submit()
	{
		if (!m_renderBatch->vertexCount || !m_renderBatch->elementCount)
			return;

		auto& camera = m_scene->getCamera();

		m_renderBatch->vbo->setBufferData(m_renderBatch->vertexCount * sizeof(Vertex), (float*)m_renderBatch->vertexPtr);
		m_renderBatch->ebo->setBufferData(m_renderBatch->elementCount * sizeof(unsigned int), m_renderBatch->elementPtr);

		m_renderBatch->bind();
		m_renderBatch->shader->setMat("u_projection", camera.getProjectionMatrix());
		m_renderBatch->shader->setMat("u_view", camera.getViewMatrix());

		glDrawElements(GL_TRIANGLES, (GLsizei)m_renderBatch->elementCount, GL_UNSIGNED_INT, nullptr);

		m_renderBatch->reset();
	}
	void OpenGLRenderer::finish()
	{
		submit();
	}

	void OpenGLRenderer::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
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

		m_renderBatch->elementPtr[m_renderBatch->elementCount + 0] = 0;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 1] = 1;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 2] = 2;

		m_renderBatch->elementPtr[m_renderBatch->elementCount + 3] = 0;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 4] = 2;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 5] = 3;

		m_renderBatch->elementCount += 6;
	}
	void OpenGLRenderer::renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint)
	{
		for (int i = 0; i < RenderData::QUAD_VERTICES; ++i)
		{
			auto& vertex = m_renderBatch->vertexPtr[m_renderBatch->vertexCount];

			vertex.position = transform * glm::vec4{ RenderData::QUAD_VERTEX_POSITIONS[i], 1.0f };
			vertex.color = textureTint;
			vertex.textureCoordinate = RenderData::QUAD_TEXTURE_COORDINATES[i];
			vertex.textureIndex = (float)m_renderBatch->textureCount;
			vertex.textureScale = textureScale;
			vertex.entityId = 0;

			m_renderBatch->textureSlots[m_renderBatch->textureCount] = texture;

			++m_renderBatch->vertexCount;
			++m_renderBatch->textureCount;
		}

		m_renderBatch->elementPtr[m_renderBatch->elementCount + 0] = 0;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 1] = 1;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 2] = 2;

		m_renderBatch->elementPtr[m_renderBatch->elementCount + 3] = 0;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 4] = 2;
		m_renderBatch->elementPtr[m_renderBatch->elementCount + 5] = 3;

		m_renderBatch->elementCount += 6;
	}
}
