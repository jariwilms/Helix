#include "stdafx.hpp"
#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(unsigned int width, unsigned int height)
	{
		glGenFramebuffers(1, &m_objectId);
		
		bind();

		m_texture = std::make_shared<OpenGLTexture>(width, height, 4, nullptr);
		m_renderBuffer = std::make_shared<OpenGLRenderBuffer>(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getId(), 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer->getId());

		verify();
		unbind();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_objectId);
	}

	void OpenGLFrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_objectId);
	}
	void OpenGLFrameBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::bindTexture() const
	{
		m_texture->bind();
	}

	bool OpenGLFrameBuffer::verify() const
	{
		int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status == GL_FRAMEBUFFER_COMPLETE) return true;

		HLX_CORE_ERROR("Framebuffer is not complete, error: ", status);//TODO: OPENGL API getstatus message ofzo idk

		return false;
	}
}
