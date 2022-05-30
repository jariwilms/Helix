#include "stdafx.hpp"
#include "VertexBuffer.hpp"

namespace hlx
{
	VertexBuffer::VertexBuffer(const float* data, GLsizei size, GLenum usage)
	{
		glGenBuffers(1, &m_objectId);
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

	void VertexBuffer::setBufferData(const float* data, GLsizei size, GLenum usage)
	{
		bind();

		glBufferData(GL_ARRAY_BUFFER, size, data, usage);

		unbind();
	}
}
