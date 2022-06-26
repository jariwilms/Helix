#include "stdafx.hpp"
#include "OpenGLRenderBuffer.hpp"

namespace hlx
{
	OpenGLRenderBuffer::OpenGLRenderBuffer(unsigned int width, unsigned int height, int format)
	{
		glGenRenderbuffers(1, &m_objectId);

		bind();

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		unbind();
	}
	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_objectId);
	}

	void OpenGLRenderBuffer::bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_objectId);
	}
	void OpenGLRenderBuffer::unbind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}
