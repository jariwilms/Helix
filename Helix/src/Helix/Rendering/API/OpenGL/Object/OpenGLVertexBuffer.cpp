#include "stdafx.hpp"

#include "OpenGLVertexBuffer.hpp"

namespace hlx
{
	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glCreateBuffers(1, &m_objectId);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, const float* data)
		: VertexBuffer{ size }
	{
		glCreateBuffers(1, &m_objectId);

		if (data) setBufferData(size, data);
		else resize(size);
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
	}

	void OpenGLVertexBuffer::reset()
	{
		setBufferData(m_bufferSize, nullptr);
	}

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
	{
		m_layout = layout;
	}

	void OpenGLVertexBuffer::setBufferData(size_t size, const float* data)
	{
		bind();

		if (size > m_bufferSize)
		{
			size = m_bufferSize;
			HLX_CORE_ERROR("Data size is greater than buffer size");
		}

		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}
