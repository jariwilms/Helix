#include "stdafx.hpp"
#include "OpenGLUniformBuffer.hpp"

namespace hlx
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int blockIndex, unsigned int blockBinding, size_t size, const void* data)
		: UniformBuffer(blockIndex, blockBinding)
	{
		glCreateBuffers(1, &m_id);
		glBindBufferBase(GL_UNIFORM_BUFFER, m_blockBinding, m_id);

		setData(size, data);

		unbind();
	}
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		if (isBound()) unbind();
		
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLUniformBuffer::bind() const
	{
		if (isBound()) return;

		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		s_boundUniformBufferId = m_id;
	}
	void OpenGLUniformBuffer::unbind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		s_boundUniformBufferId = 0;
	}
	bool OpenGLUniformBuffer::isBound() const
	{
		return s_boundUniformBufferId == m_id;
	}

	void OpenGLUniformBuffer::setData(size_t size, const void* data)
	{
		bind();

		glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
		
		if (data) m_dataSize = size;
		m_dataLimit = size;
	}
	void OpenGLUniformBuffer::setSubData(size_t size, const void* data)
	{
		setSubData(size, 0, data);
	}
	void OpenGLUniformBuffer::setSubData(size_t size, size_t offset, const void* data)
	{
		bind();

		if (offset + size > m_dataLimit)
		{
			HLX_CORE_ERROR("[Uniform buffer] subdata exceeds buffer size");
			return;
		}

		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		
		m_dataSize = offset + size;
	}
}
