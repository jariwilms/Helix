#include "stdafx.hpp"
#include "ElementBuffer.hpp"

namespace hlx
{
	ElementBuffer::ElementBuffer(const void* data, size_t size, GLenum usage)
	{
		glGenBuffers(1, &m_objectId);
		setBufferData(data, size, usage);
	}

	ElementBuffer::~ElementBuffer()
	{
		glDeleteBuffers(1, &m_objectId);
	}

	void ElementBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_objectId);
	}

	void ElementBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void ElementBuffer::setBufferData(const void* data, size_t size, GLenum usage)
	{
		bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

		unbind();
	}
}
