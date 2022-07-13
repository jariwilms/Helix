#include "stdafx.hpp"
#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferBlueprint blueprint)
		: m_target{ GL_FRAMEBUFFER }
	{
		glGenFramebuffers(1, &m_id);
		


		for (const auto& blueprint : blueprint.textureBlueprints)
			m_textures.push_back(std::make_shared<OpenGLTexture>(blueprint, nullptr));

		for (const auto& blueprint : blueprint.renderBufferBlueprints)
			m_renderBuffers.push_back(std::make_shared<OpenGLRenderBuffer>(blueprint));

		

		bind();
		attach();

		auto status = glCheckFramebufferStatus(m_target);
		HLX_CORE_ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Invalid framebuffer: status {0}", status);

		unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, attachments);

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
	void OpenGLFrameBuffer::bindTextures() const
	{
		unsigned int index{};
		
		for (const auto& texture : m_textures)
		{
			texture->bindUnit(index);
			++index;
		}
	}

	void OpenGLFrameBuffer::attach()
	{
		unsigned int offset{};
		std::vector<unsigned int> attachments{};
		
		for (const auto& texture : m_textures)
		{
			glFramebufferTexture2D(m_target, GL_COLOR_ATTACHMENT0 + offset, GL_TEXTURE_2D, texture->getId(), 0);
			attachments.push_back(GL_COLOR_ATTACHMENT0 + offset);
			
			++offset;
		}

		for (const auto& renderBuffer : m_renderBuffers)
		{
			auto attachment = OpenGL::getRenderBufferAttachment(renderBuffer->getAttachment());
			glFramebufferRenderbuffer(m_target, attachment, GL_RENDERBUFFER, renderBuffer->getId());
		}

		glDrawBuffers(offset + 1, attachments.data());
	}
}
