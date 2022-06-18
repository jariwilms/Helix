#pragma once

#include "Helix/Rendering/Object/RenderBuffer.hpp"

namespace hlx
{
	class OpenGLRenderBuffer : public RenderBuffer
	{
	public:
		OpenGLRenderBuffer(unsigned int width, unsigned int height, int format = GL_DEPTH24_STENCIL8);
		~OpenGLRenderBuffer();

		void bind() const override;
		void unbind() const override;
	};
}
