#include "stdafx.hpp"
#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferBlueprint blueprint)
		: m_target{ GL_FRAMEBUFFER }
	{
		glGenFramebuffers(1, &m_id);
		


		for (const auto& [name, blueprint] : blueprint.textureBlueprints)
			m_textures.emplace_back(std::move(std::make_pair(name, std::make_shared<OpenGLTexture>(blueprint, nullptr))));

		for (const auto& [name, blueprint] : blueprint.renderBufferBlueprints)
			m_renderBuffers.emplace_back(std::move(std::make_pair(name, std::make_shared<OpenGLRenderBuffer>(blueprint))));

		

		bind(FrameBufferTarget::Default);
		attach();

		auto status = glCheckFramebufferStatus(m_target);
		HLX_CORE_ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Invalid framebuffer: status {0}", status);

		unbind();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		if (s_boundFrameBufferId == m_id) unbind();
		glDeleteFramebuffers(1, &m_id);
	}

	bool OpenGLFrameBuffer::bind(FrameBufferTarget target) const
	{
		//if (s_boundFrameBufferId == m_id) return false;

		glBindFramebuffer(OpenGL::getFrameBufferTarget(target), m_id);
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
		
		for (const auto& [name, texture] : m_textures)
		{
			texture->bindUnit(index);
			++index;
		}
	}

	const std::shared_ptr<Texture> OpenGLFrameBuffer::getTexture(const std::string& name) const
	{
		return std::find_if(m_textures.begin(), m_textures.end(), [&](const auto& _) -> bool { return _.first == name; })->second;
	}
	const std::vector<std::shared_ptr<Texture>> OpenGLFrameBuffer::getTextures() const
	{
		std::vector<std::shared_ptr<Texture>> textures{};

		for (const auto& [name, texture] : m_textures)
			textures.push_back(texture);

		return textures;
	}
	const std::vector<std::shared_ptr<RenderBuffer>> OpenGLFrameBuffer::getRenderBuffers() const
	{
		std::vector < std::shared_ptr<RenderBuffer>> renderBuffers{};

		for (const auto& [name, renderBuffer] : m_renderBuffers)
			renderBuffers.push_back(renderBuffer);

		return renderBuffers;
	}
	
	void OpenGLFrameBuffer::attach()
	{
		unsigned int offset{};
		
		for (const auto& [name, texture] : m_textures)
		{
			glFramebufferTexture2D(m_target, GL_COLOR_ATTACHMENT0 + offset, GL_TEXTURE_2D, texture->getId(), 0);
			m_attachments.push_back(GL_COLOR_ATTACHMENT0 + offset);
			
			++offset;
		}

		for (const auto& [name, renderBuffer] : m_renderBuffers)
		{
			auto attachment = OpenGL::getRenderBufferAttachment(renderBuffer->getAttachment());
			glFramebufferRenderbuffer(m_target, attachment, GL_RENDERBUFFER, renderBuffer->getId());
		}

		glDrawBuffers(offset, m_attachments.data());
	}
}
