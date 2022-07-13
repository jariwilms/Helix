#include "stdafx.hpp"
#include "RenderBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLRenderBuffer.hpp"

namespace hlx
{
	std::shared_ptr<RenderBuffer> RenderBuffer::create(RenderBufferBlueprint blueprint)
	{
		return std::make_shared<OpenGLRenderBuffer>(blueprint);
	}
}
