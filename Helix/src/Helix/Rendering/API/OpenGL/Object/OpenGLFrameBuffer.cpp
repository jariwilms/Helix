#include "stdafx.hpp"
#include "OpenGLFrameBuffer.hpp"
unsigned int rbo;
namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(unsigned int width, unsigned int height)
	{
		glCreateFramebuffers(1, &m_objectId);
		bind();

		m_texture = std::make_unique<OpenGLTexture>(width, height, 4, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getId(), 0);


		//TODO: renderbuffer class

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);


		auto a = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		HLX_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete. ERROR [{0}]");
		unbind();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_objectId);
		glDeleteRenderbuffers(1, &rbo);
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
}
