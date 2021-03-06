#include "stdafx.hpp"
#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferBlueprint blueprint)
		: m_target{ GL_FRAMEBUFFER }
	{
		glGenFramebuffers(1, &m_id);
		
		auto test = s_boundFrameBufferTargetId.size();

		for (const auto& [name, blueprint] : blueprint.textureBlueprints)
			m_textures.insert(std::make_pair(name, std::make_shared<OpenGLTexture>(blueprint, nullptr)));

		for (const auto& [name, blueprint] : blueprint.renderBufferBlueprints)
			m_renderBuffers.insert(std::make_pair(name, std::make_shared<OpenGLRenderBuffer>(blueprint)));

		

		bind(FrameBufferTarget::Default);
		attach();

		auto status = glCheckFramebufferStatus(m_target);
		HLX_CORE_ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Invalid framebuffer: status {0}", status);

		unbind();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		if (isBound()) unbind();
		
		glDeleteFramebuffers(1, &m_id);
	}

	void OpenGLFrameBuffer::bind(FrameBufferTarget target) const
	{
		if (isBound() && target == s_boundFrameBufferTarget) return;
		if (target != s_boundFrameBufferTarget) unbind();

		glBindFramebuffer(OpenGL::getFrameBufferTarget(target), m_id);
		s_boundFrameBufferTarget = target;
		s_boundFrameBufferTargetId[static_cast<int>(target)] = m_id;
	}
	void OpenGLFrameBuffer::unbind() const
	{
		glBindFramebuffer(OpenGL::getFrameBufferTarget(s_boundFrameBufferTarget), 0);
		s_boundFrameBufferTargetId[static_cast<int>(s_boundFrameBufferTarget)] = 0;
	}
	bool OpenGLFrameBuffer::isBound() const
	{
		return s_boundFrameBufferTargetId[static_cast<int>(s_boundFrameBufferTarget)] == m_id;
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
