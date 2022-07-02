#include "stdafx.hpp"
#include "VertexBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexBuffer.hpp"

namespace hlx
{
	std::shared_ptr<VertexBuffer> VertexBuffer::create(unsigned int count, const float* data)
	{
		return std::make_shared<OpenGLVertexBuffer>(count, data);
	}
}
