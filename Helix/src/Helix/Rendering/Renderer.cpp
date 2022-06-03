#include "stdafx.hpp"
#include "Renderer.hpp"

namespace hlx
{
	void Renderer::init()
	{
		s_renderAPI = new OpenGLRenderer{};
	}

	void Renderer::clearBuffer()
	{
		s_renderAPI->clearBuffer();
	}

	void Renderer::clearBackground(glm::vec4 color)
	{
		s_renderAPI->clearBackground(color);
	}

	void Renderer::render(const hlx::VertexArray& vertexArray)
	{
		s_renderAPI->render(vertexArray);
	}

	RenderAPI* Renderer::s_renderAPI;
}
