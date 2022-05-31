#include "stdafx.hpp"
#include "OpenGlRenderer.hpp"

namespace hlx
{
	OpenGlRenderer::OpenGlRenderer()
	{

	}

	OpenGlRenderer::~OpenGlRenderer()
	{
		
	}

	void OpenGlRenderer::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGlRenderer::clearBackground(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGlRenderer::drawIndexed(const VertexArray& vertexArray) //TODO: abstract naar generic draw/submit call
	{
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, vertexArray.getElementBuffer().getCount(), GL_UNSIGNED_INT, nullptr);
	}
}
