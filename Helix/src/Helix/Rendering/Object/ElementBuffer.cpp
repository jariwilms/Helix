#include "stdafx.hpp"
#include "ElementBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLElementBuffer.hpp"

namespace hlx
{
	std::shared_ptr<ElementBuffer> ElementBuffer::create(unsigned int count, const unsigned int* data)
	{
		return std::make_shared<OpenGLElementBuffer>(count, data);
	}
}
