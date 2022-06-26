#include "stdafx.hpp"
#include "Renderer.hpp"

namespace hlx
{
	void Renderer::init()
	{
		s_renderAPI = new OpenGLRenderer{};
	}

	void Renderer::start(const Camera& camera)
	{
		s_renderAPI->start(camera);
	}
	void Renderer::finish()
	{
		s_renderAPI->finish();
	}

	void Renderer::clearBuffer()
	{
		s_renderAPI->clearBuffer();
	}
	void Renderer::clearBackground(glm::vec4 color)
	{
		s_renderAPI->clearBackground(color);
	}



	void Renderer::renderQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
	{
		s_renderAPI->renderQuad(position, scale, color);
	}
	void Renderer::renderQuad(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint)
	{
		s_renderAPI->renderQuad(position, scale, texture, textureScale, textureTint);
	}

	void Renderer::renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		s_renderAPI->renderQuad(position, rotation, scale, color);
	}
	void Renderer::renderQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint)
	{
		s_renderAPI->renderQuad(position, rotation, scale, texture, textureScale, textureTint);
	}

	void Renderer::renderQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		s_renderAPI->renderQuad(transform, color);
	}
	void Renderer::renderQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, float textureScale, const glm::vec4& textureTint)
	{
		s_renderAPI->renderQuad(transform, texture, textureScale, textureTint);
	}



	void Renderer::renderModel(Model& model, const glm::mat4& transform)
	{
		s_renderAPI->renderModel(model, transform);
	}



	void Renderer::poll()
	{
		s_renderAPI->poll();
	}
	RenderStatistics Renderer::measure()
	{
		return s_renderAPI->measure();
	}

	RenderAPI* Renderer::s_renderAPI;
}
