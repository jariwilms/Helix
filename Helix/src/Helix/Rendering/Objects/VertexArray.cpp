#include "stdafx.hpp"
#include "VertexArray.hpp"

namespace hlx
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_objectId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_objectId);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_objectId);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void VertexArray::setLayout(const VertexBuffer& buffer, const BufferLayout& layout)
	{
		bind();
		buffer.bind();

		GLint64 offset{};
		const auto& attributes = layout.getAttributes();

		for (GLuint i = 0; i < attributes.size(); ++i)
		{
			const auto& attribute = attributes[i];

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attribute.size, attribute.type, attribute.normalized, layout.getStride(), (const void*)offset);

			auto result = attribute.size * GL::getSizeOfGLtype(attribute.type);
			offset += result;
		}

		buffer.unbind();
	}
}
