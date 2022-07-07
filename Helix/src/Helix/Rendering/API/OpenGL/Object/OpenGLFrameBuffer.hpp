#pragma once

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Helix/Rendering/API/OpenGL/Object/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/Object/FrameBuffer.hpp"

namespace hlx
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(glm::uvec2 dimensions);
		~OpenGLFrameBuffer();

		bool bind() const override;
		void unbind() const override;
		void bindTexture() const override;

		inline std::shared_ptr<Texture> getTexture() override { return m_texture; }

	private:
		std::shared_ptr<OpenGLTexture> m_texture;
		std::shared_ptr<OpenGLRenderBuffer> m_renderBuffer;
	};
}
