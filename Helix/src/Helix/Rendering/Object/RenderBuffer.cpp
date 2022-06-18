#include "stdafx.hpp"
#include "RenderBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLRenderBuffer.hpp"

namespace hlx
{
	std::shared_ptr<RenderBuffer> hlx::RenderBuffer::create(unsigned int width, unsigned int height, int format)
	{
		return std::make_shared<OpenGLRenderBuffer>(width, height, format);
	}
}
