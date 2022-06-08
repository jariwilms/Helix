#include "stdafx.hpp"

#include "OpenGLElementBuffer.hpp"

namespace hlx
{
	OpenGLElementBuffer::OpenGLElementBuffer(size_t size, const unsigned int* data)
	{
		glCreateBuffers(1, &m_objectId);
		resize(size);
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

	void OpenGLElementBuffer::resize(size_t size)
	{
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
		unbind();
	}

	void OpenGLElementBuffer::reset()
	{
		setBufferData(m_bufferSize, nullptr);
	}

	size_t OpenGLElementBuffer::getSize() const
	{
		return m_bufferSize;
	}

	void OpenGLElementBuffer::setBufferData(size_t size, const unsigned int* data)
	{
		bind();

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);

		unbind();
	}
}
