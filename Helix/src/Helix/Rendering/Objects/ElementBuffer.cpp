#include "stdafx.hpp"
#include "ElementBuffer.hpp"

#include "API/OpenGL/Objects/OpenGLElementBuffer.hpp"

namespace hlx
{
	std::shared_ptr<ElementBuffer> ElementBuffer::create(unsigned int* data, int size)
	{
		return std::make_shared<OpenGLElementBuffer>(data, size);
	}
}
