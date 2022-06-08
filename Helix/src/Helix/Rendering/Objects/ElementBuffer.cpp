#include "stdafx.hpp"
#include "ElementBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Objects/OpenGLElementBuffer.hpp"

namespace hlx
{
	std::shared_ptr<ElementBuffer> ElementBuffer::create(size_t size, const unsigned int* data)
	{
		return std::make_shared<OpenGLElementBuffer>(size, data);
	}
}
