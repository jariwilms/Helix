#include "stdafx.hpp"

#include "OpenGLVertexBuffer.hpp"

namespace hlx
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, const float* data)
	{
		glCreateBuffers(1, &m_objectId);

		if (data) setBufferData(size, data);
		else resize(size);

		unbind();
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_objectId);
	}

	void OpenGLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_objectId);
	}
	void OpenGLVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::resize(size_t size)
	{
		bind();

		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
		m_bufferSize = size;
	}
	void OpenGLVertexBuffer::reset()
	{
		resize(0);
	}

	void OpenGLVertexBuffer::setBufferData(size_t size, const float* data)
	{
		bind();

		if (size > m_bufferSize) resize(size);

		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}
