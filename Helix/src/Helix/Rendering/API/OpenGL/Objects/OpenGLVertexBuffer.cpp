#include "stdafx.hpp"

#include "OpenGLVertexBuffer.hpp"

namespace hlx
{
	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glCreateBuffers(1, &m_objectId);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, int size)
	{
		glCreateBuffers(1, &m_objectId);
		setBufferData(data, size);
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

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
	{
		m_layout = layout;
	}

	void OpenGLVertexBuffer::setBufferData(float* data, int size)
	{
		bind();

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		unbind();
	}
}
