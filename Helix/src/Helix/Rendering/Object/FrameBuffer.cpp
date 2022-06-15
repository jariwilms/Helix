#include "stdafx.hpp"
#include "FrameBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLFrameBuffer.hpp"

namespace hlx
{
	std::shared_ptr<FrameBuffer> FrameBuffer::create(unsigned int width, unsigned int height)
	{ 
		return std::make_shared<OpenGLFrameBuffer>(width, height); 
	}
}
