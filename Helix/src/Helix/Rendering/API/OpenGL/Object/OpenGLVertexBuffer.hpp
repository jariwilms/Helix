#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Object/VertexBuffer.hpp"

namespace hlx
{
	template <typename T>
	class OpenGLVertexBuffer : public VertexBuffer<T>
	{
	public:
		OpenGLVertexBuffer(unsigned int count, const float* data)
			: VertexBuffer<T>{}
		{
			glCreateBuffers(1, &m_id);

			setData(count, data);

			unbind();

		}
		~OpenGLVertexBuffer() override
		{
			if (isBound()) unbind();

			glDeleteBuffers(1, &m_id);
		}
		
		void bind() const override
		{
			if (isBound()) return;

			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			s_boundVertexBufferId = m_id;
		}
		void unbind() const override
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			s_boundVertexBufferId = 0;
		}
		bool isBound() const override
		{
			return s_boundVertexBufferId == m_id;
		}

		void setData(unsigned int count, const float* data) override
		{
			bind();

			size_t totalSize = count * m_typeSize;
			glBufferData(GL_ARRAY_BUFFER, totalSize, data, GL_STATIC_DRAW);

			if (data) m_dataCount = count;
			m_dataLimit = count;
		}
		void setSubData(unsigned int count, const float* data) override
		{
			setSubData(count, 0, data);
		}
		void setSubData(unsigned int count, unsigned int offset, const float* data) override
		{
			bind();

			if (offset + count > m_dataLimit)
			{
				HLX_CORE_ERROR("[VertexBuffer] subdata overflow");
				return;
			}

			size_t totalSize = count * m_typeSize;
			size_t byteOffset = offset * m_typeSize;

			glBufferSubData(GL_ARRAY_BUFFER, byteOffset, totalSize, data);
			m_dataCount = static_cast<unsigned int>(offset + count);
		}
	};
}
