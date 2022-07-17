#include "stdafx.hpp"

#include "OpenGLVertexBuffer.hpp"

namespace hlx
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int count, const float* data)
	{
		glCreateBuffers(1, &m_id);
		
		setData(count, data);

		unbind();
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		if (isBound()) unbind();
		
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLVertexBuffer::bind() const
	{
		if (isBound()) return;

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		s_boundVertexBufferId = m_id;
	}
	void OpenGLVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		s_boundVertexBufferId = 0;
	}
	bool OpenGLVertexBuffer::isBound() const
	{
		return s_boundVertexBufferId == m_id;
	}

	void OpenGLVertexBuffer::setData(unsigned int count, const float* data)
	{
		bind();

		auto size = count * sizeof(float);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		if (data) m_dataCount = count;
		m_dataLimit = count;
	}
	void OpenGLVertexBuffer::setSubData(unsigned int count, const float* data)
	{
		setSubData(count, 0, data);
	}
	void OpenGLVertexBuffer::setSubData(unsigned int count, unsigned int offset, const float* data)
	{
		bind();

		if (offset + count > m_dataLimit)
		{
			HLX_CORE_ERROR("[Vertex buffer] subdata overflow");
			return;
		}

		auto size = count * sizeof(float);
		offset *= sizeof(float);
		
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		m_dataCount += static_cast<unsigned int>(size);
	}
}
