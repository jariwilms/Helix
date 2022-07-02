#include "stdafx.hpp"
#include "OpenGLRenderBuffer.hpp"

namespace hlx
{
	OpenGLRenderBuffer::OpenGLRenderBuffer(glm::uvec2 dimensions, int format)
	{
		glGenRenderbuffers(1, &m_id);

		allocate(dimensions, format);

		unbind();
	}
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_id);
	}

	void OpenGLRenderBuffer::bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_id);
	}
	void OpenGLRenderBuffer::unbind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void OpenGLRenderBuffer::allocate(glm::uvec2 dimensions, int format)
	{
		bind();
		
		glRenderbufferStorage(GL_RENDERBUFFER, format, dimensions.x, dimensions.y);
	}
}
