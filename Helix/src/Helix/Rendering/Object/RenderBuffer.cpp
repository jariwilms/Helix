#include "stdafx.hpp"
#include "RenderBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLRenderBuffer.hpp"

namespace hlx
{
	std::shared_ptr<RenderBuffer> hlx::RenderBuffer::create(glm::uvec2 dimensions, int format)
	{
		return std::make_shared<OpenGLRenderBuffer>(dimensions, format);
	}
}
