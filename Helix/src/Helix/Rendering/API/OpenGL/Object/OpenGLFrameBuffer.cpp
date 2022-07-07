#include "stdafx.hpp"
#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(glm::uvec2 dimensions)
	{
		glGenFramebuffers(1, &m_id);
		
		bind();

		m_texture = std::make_shared<OpenGLTexture>(dimensions, 4, nullptr);
		m_renderBuffer = std::make_shared<OpenGLRenderBuffer>(dimensions);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getId(), 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer->getId());

		int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) HLX_CORE_ERROR("Framebuffer is not complete, error: ", status);//TODO: OPENGL API getstatus message ofzo idk

		unbind();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_id);
	}

	bool OpenGLFrameBuffer::bind() const
	{
		if (s_boundFrameBufferId == m_id) return false;

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		s_boundFrameBufferId = m_id;

		return true;
	}
	void OpenGLFrameBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		s_boundFrameBufferId = 0;
	}
	
	void OpenGLFrameBuffer::bindTexture() const
	{
		m_texture->bind();
	}
}
