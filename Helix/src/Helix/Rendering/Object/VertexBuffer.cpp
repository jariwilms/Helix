#include "stdafx.hpp"
#include "VertexBuffer.hpp"

#include "Helix/Rendering/API/OpenGL/Object/OpenGLVertexBuffer.hpp"

namespace hlx
{
	std::shared_ptr<VertexBuffer> VertexBuffer::create(size_t size, const float* data)
	{
		return std::make_shared<OpenGLVertexBuffer>(size, data);
	}
}
