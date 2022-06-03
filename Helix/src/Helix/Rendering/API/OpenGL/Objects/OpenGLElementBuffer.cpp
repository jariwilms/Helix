#include "stdafx.hpp"

#include "OpenGLElementBuffer.hpp"

namespace hlx
{
	OpenGLElementBuffer::OpenGLElementBuffer(unsigned int* data, int size)
	{
		glCreateBuffers(1, &m_objectId);
		setBufferData(data, size);
	}

	OpenGLElementBuffer::~OpenGLElementBuffer()
	{
		glDeleteBuffers(1, &m_objectId);
	}

	void OpenGLElementBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_objectId);
	}

	void OpenGLElementBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	GLsizei OpenGLElementBuffer::getSize() const
	{
		return m_size;
	}

	void OpenGLElementBuffer::setBufferData(unsigned int* data, int size)
	{
		bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		m_size = size / (GLsizei)sizeof(unsigned int);

		unbind();
	}
}
