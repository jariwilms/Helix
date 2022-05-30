#include "stdafx.hpp"
#include "ElementBuffer.hpp"

namespace hlx
{
	ElementBuffer::ElementBuffer(const unsigned int* data, GLsizei size, GLenum usage)
		:m_count{ size / (GLsizei)sizeof(unsigned int) }
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

	GLsizei ElementBuffer::getCount() const
	{
		return m_count;
	}

	void ElementBuffer::setBufferData(const unsigned int* data, GLsizei size, GLenum usage)
	{
		bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

		unbind();
	}
}
