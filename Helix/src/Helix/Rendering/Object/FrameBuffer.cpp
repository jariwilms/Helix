#include "stdafx.hpp"
#include "FrameBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLFrameBuffer.hpp"

namespace hlx
{
	std::shared_ptr<FrameBuffer> FrameBuffer::create(glm::uvec2 dimensions)
	{ 
		return std::make_shared<OpenGLFrameBuffer>(dimensions); 
	}
}
