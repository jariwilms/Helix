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

	void Renderer::submit()
	{
		s_renderAPI->submit();
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

	void Renderer::renderQuad(const glm::vec3& position)
	{
		s_renderAPI->renderQuad(position);
	}

	RenderAPI* Renderer::s_renderAPI;
}
