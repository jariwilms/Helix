#pragma once

#include "Helix/Rendering/Object/RenderBuffer.hpp"

namespace hlx
{
	class OpenGLRenderBuffer : public RenderBuffer
	{
	public:
		OpenGLRenderBuffer(RenderBufferBlueprint blueprint);
		~OpenGLRenderBuffer();

		bool bind() const override;
		void unbind() const override;

	private:
		void allocate();

		int m_target;
		int m_internalFormat;
	};
}
