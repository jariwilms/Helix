#include "stdafx.hpp"
#include "VertexBuffer.hpp"

namespace hlx
{
	VertexBuffer::VertexBuffer()
	{
		glCreateBuffers(1, &m_objectId);
	}

	VertexBuffer::VertexBuffer(const float* data, GLsizei size, GLenum usage)
	{
		glCreateBuffers(1, &m_objectId);
		setBufferData(data, size, usage);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_objectId);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_objectId);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const hlx::BufferLayout& VertexBuffer::getLayout() const
	{
		return m_layout;
	}

	void VertexBuffer::setLayout(const BufferLayout& layout)
	{
		m_layout = layout;
	}

	void VertexBuffer::setBufferData(const float* data, GLsizei size, GLenum usage)
	{
		bind();

		glBufferData(GL_ARRAY_BUFFER, size, data, usage);

		unbind();
	}
}
