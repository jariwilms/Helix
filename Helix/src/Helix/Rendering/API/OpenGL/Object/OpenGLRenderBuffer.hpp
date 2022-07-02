#pragma once

#include "Helix/Rendering/Object/RenderBuffer.hpp"

namespace hlx
{
	class OpenGLRenderBuffer : public RenderBuffer
	{
	public:
		OpenGLRenderBuffer(glm::uvec2 dimensions, int format = GL_DEPTH24_STENCIL8);
		~OpenGLRenderBuffer();

		void bind() const override;
		void unbind() const override;

		void allocate(glm::uvec2 dimensions, int format) override;
	};
}
