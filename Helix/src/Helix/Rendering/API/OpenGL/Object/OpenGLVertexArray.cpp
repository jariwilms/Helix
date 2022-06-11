#include "stdafx.hpp"
#include "OpenGLVertexArray.hpp"

namespace hlx
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_objectId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_objectId);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_objectId);
		m_elementBuffer->bind();
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer)
	{
		HLX_CORE_ASSERT(buffer->getLayout().getAttributes().size(), "Buffer has no size");

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

	void OpenGLVertexArray::setElementBuffer(const std::shared_ptr<ElementBuffer> buffer)
	{
		m_elementBuffer = buffer;
	}
}
