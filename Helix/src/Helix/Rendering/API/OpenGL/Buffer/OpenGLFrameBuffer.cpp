#include "stdafx.hpp"

#include "OpenGLFrameBuffer.hpp"

namespace hlx
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const Vector2u& dimensions, std::span<const TextureManifest> textureManifests, std::span<const RenderBufferManifest> renderBufferManifests)
		: FrameBuffer{ dimensions }
	{
		m_id = OpenGL::create_framebuffer();
		
		std::for_each(textureManifests.begin(), textureManifests.end(), std::bind(std::mem_fn(&OpenGLFrameBuffer::attach_texture), this, std::placeholders::_1));
		std::for_each(renderBufferManifests.begin(), renderBufferManifests.end(), std::bind(std::mem_fn(&OpenGLFrameBuffer::attach_renderbuffer), this, std::placeholders::_1));

		if (m_colorBuffers.empty()) 
		{
			OpenGL::framebuffer_readbuffer(m_id, GL_NONE);
			OpenGL::framebuffer_drawbuffer(m_id, GL_NONE);
		}
		else
		{
			OpenGL::framebuffer_drawbuffers(m_id, m_colorBuffers);
		}

		OpenGL::check_framebuffer_status(m_id);
	}
    OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		OpenGL::delete_framebuffer(m_id);
	}

	void OpenGLFrameBuffer::bind(Target target) const
	{
		OpenGL::bind_framebuffer(m_id, target);
	}
    void OpenGLFrameBuffer::bind_texture(const std::string& identifier, unsigned int slot) const
    {
		m_textures.at(identifier)->bind(slot);
    }

    void OpenGLFrameBuffer::attach_texture(const TextureManifest& textureManifest)
    {
		const auto& [name, attachment, blueprint] = textureManifest;
        const auto& glTexture = std::static_pointer_cast<OpenGLTexture2D>(blueprint.build(m_dimensions));

		auto internalAttachment = OpenGL::framebuffer_attachment(attachment);
		if (attachment == Attachment::Color)
		{
			internalAttachment += static_cast<GLenum>(m_colorBuffers.size());
			m_colorBuffers.push_back(internalAttachment);
		}

        OpenGL::attach_framebuffer_texture(m_id, glTexture->id(), internalAttachment, 0);
        m_textures.emplace(name, glTexture);
    }
    void OpenGLFrameBuffer::attach_renderbuffer(const RenderBufferManifest& renderBufferManifest)
    {
		const auto& [name, attachment, blueprint] = renderBufferManifest;
		const auto& glRenderBuffer = std::static_pointer_cast<OpenGLRenderBuffer>(blueprint.build(m_dimensions));

		const auto& internalAttachment = OpenGL::framebuffer_attachment(attachment);

		OpenGL::attach_framebuffer_renderbuffer(m_id, glRenderBuffer->id(), internalAttachment);
		m_renderBuffers.emplace(name, glRenderBuffer);
    }
}
