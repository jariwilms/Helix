#pragma once

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Helix/Rendering/API/OpenGL/Object/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/Object/FrameBuffer.hpp"

namespace hlx
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(FrameBufferBlueprint blueprint);
		~OpenGLFrameBuffer();

		bool bind() const override;
		void unbind() const override;
		void bindTextures() const override;

		std::vector<std::shared_ptr<Texture>> getTextures() override { return std::vector<std::shared_ptr<Texture>>(m_textures.begin(), m_textures.end()); }
		std::vector<std::shared_ptr<RenderBuffer>> getRenderBuffers() override { return std::vector<std::shared_ptr<RenderBuffer>>(m_renderBuffers.begin(), m_renderBuffers.end()); }

	private:
		void attach();

		int m_target;
		
		std::vector<std::shared_ptr<OpenGLTexture>> m_textures;
		std::vector<std::shared_ptr<OpenGLRenderBuffer>> m_renderBuffers;
	};
}
