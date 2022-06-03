#include "stdafx.hpp"
#include "VertexBuffer.hpp"

#include "API/OpenGL/Objects/OpenGLVertexBuffer.hpp"

namespace hlx
{
	std::shared_ptr<VertexBuffer> VertexBuffer::create()
	{
		return std::make_shared<OpenGLVertexBuffer>();
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::create(float* data, int size)
	{
		return std::make_shared<OpenGLVertexBuffer>(data, size);
	}

	const hlx::BufferLayout& VertexBuffer::getLayout() const
	{
		return m_layout;
	}
}
