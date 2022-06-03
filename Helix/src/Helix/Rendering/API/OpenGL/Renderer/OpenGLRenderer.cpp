#include "stdafx.hpp"
#include "OpenGLRenderer.hpp"

namespace hlx
{
	void OpenGLRenderer::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer::clearBackground(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderer::render(const VertexArray& vertexArray) //TODO: abstract naar generic draw/submit call
	{
		vertexArray.bind();
		glDrawElements(GL_TRIANGLES, vertexArray.getElementBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);
	}
}
