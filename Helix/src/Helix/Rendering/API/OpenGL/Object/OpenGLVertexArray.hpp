#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Object/VertexArray.hpp"

namespace hlx
{
	template <typename T>
	class OpenGLVertexArray : public VertexArray<T>
	{
	public:
		OpenGLVertexArray()
			: VertexArray<T>{}
		{
			glCreateVertexArrays(1, &m_id);
		}
		~OpenGLVertexArray() override
		{
			if (isBound()) unbind();

			glDeleteVertexArrays(1, &m_id);
		}

		void bind() const override
		{
			if (isBound() && m_elementBuffer->isBound()) return;

			glBindVertexArray(m_id);
			s_boundVertexArrayId = m_id;

			m_elementBuffer->bind();
		}
		void unbind() const override
		{
			glBindVertexArray(0);
			s_boundVertexArrayId = 0;

			m_elementBuffer->unbind();
		}
		bool isBound() const override
		{
			return s_boundVertexArrayId == m_id;
		}

		void addVertexBuffer(const std::shared_ptr<VertexBuffer<T>> buffer) override
		{
			HLX_CORE_ASSERT(m_elementBuffer, "[VertexArray] No ElementBuffer has been set");
			HLX_CORE_ASSERT(!buffer->getLayout().getAttributes().empty(), "[VertexArray] VertexBuffer has no layout");

			bind();
			buffer->bind();

			unsigned int offset{};
			auto& layout = buffer->getLayout();

			for (const auto& attribute : layout.getAttributes())
			{
				glEnableVertexAttribArray(m_vertexAttributeIndex);
				glVertexAttribPointer(m_vertexAttributeIndex, attribute.size, attribute.type, attribute.normalized, layout.getStride(), (const void*)((uint64_t)offset));
				++m_vertexAttributeIndex;

				auto result = attribute.size * OpenGL::getSizeOfType(attribute.type);
				offset += result;
			}

			m_vertexBuffers.emplace_back(buffer);
			buffer->unbind();
		}
		void setElementBuffer(const std::shared_ptr<ElementBuffer> buffer) override
		{
			m_elementBuffer = buffer;
		}
	};
}
