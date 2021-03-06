#include "stdafx.hpp"

#include "OpenGLElementBuffer.hpp"

namespace hlx
{
	OpenGLElementBuffer::OpenGLElementBuffer(unsigned int count, const unsigned int* data)
		: ElementBuffer{}
	{
		glCreateBuffers(1, &m_id);
		
		setData(count, data);

		unbind();
	}
	OpenGLElementBuffer::~OpenGLElementBuffer()
	{
		if (isBound()) unbind();
		
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLElementBuffer::bind() const
	{
		if (isBound()) return;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		s_boundElementBufferId = m_id;
	}
	void OpenGLElementBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		s_boundElementBufferId = 0;
	}
	bool OpenGLElementBuffer::isBound() const
	{
		return s_boundElementBufferId == m_id;
	}

	void OpenGLElementBuffer::setData(unsigned int count, const unsigned int* data)
	{
		bind();

		size_t totalSize = count * sizeof(unsigned int);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalSize, data, GL_STATIC_DRAW);

		if (data) m_dataCount = count;
		m_dataLimit = count;
	}
	void OpenGLElementBuffer::setSubData(unsigned int count, const unsigned int* data)
	{
		setSubData(count, 0, data);
	}
	void OpenGLElementBuffer::setSubData(unsigned int count, unsigned int offset, const unsigned int* data)
	{
		bind();

		if (offset + count > m_dataLimit)
		{
			HLX_CORE_ERROR("[ElementBuffer] subdata overflow");
			return;
		}

		size_t totalSize = count * sizeof(unsigned int);
		size_t byteOffset = offset * sizeof(unsigned int);

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, byteOffset, totalSize, data);
		m_dataCount = static_cast<unsigned int>(offset + count);
	}
}
