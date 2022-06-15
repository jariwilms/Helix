#pragma once

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Helix/Rendering/Object/FrameBuffer.hpp"

namespace hlx
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(unsigned int width, unsigned int height);
		~OpenGLFrameBuffer();

		void bind() const override;
		void unbind() const override;

		inline std::shared_ptr<Texture> getTexture() { return m_texture; }

	private:
		std::shared_ptr<OpenGLTexture> m_texture;
	};
}
