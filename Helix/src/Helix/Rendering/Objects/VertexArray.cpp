#include "stdafx.hpp"
#include "VertexArray.hpp"

namespace hlx
{
	VertexArray::VertexArray()
		: m_vertexBufferIndex{}
	{
		glCreateVertexArrays(1, &m_objectId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_objectId);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_objectId);
		m_elementBuffer.bind();
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	const std::vector<VertexBuffer>& VertexArray::getVertexBuffers() const
	{
		return m_vertexBuffers;
	}

	void VertexArray::addVertexBuffer(const VertexBuffer& buffer)
	{
		HLX_CORE_ASSERT(buffer.getLayout().getAttributes().size(), "");

		bind();
		buffer.bind();

		GLint64 offset{};
		auto& layout = buffer.getLayout();

		for (const auto& attribute : layout.getAttributes())
		{
			glEnableVertexAttribArray(m_vertexBufferIndex);
			glVertexAttribPointer(m_vertexBufferIndex, attribute.size, attribute.type, attribute.normalized, layout.getStride(), (const void*)offset);
			++m_vertexBufferIndex;

			auto result = attribute.size * GL::getSizeOfGLtype(attribute.type);
			offset += result;
		}

		m_vertexBuffers.emplace_back(buffer);
		buffer.unbind();
	}

	const hlx::ElementBuffer& VertexArray::getElementBuffer() const
	{
		return m_elementBuffer;
	}

	void VertexArray::setElementBuffer(const ElementBuffer& buffer)
	{
		m_elementBuffer = buffer;
	}
}
