#pragma once

#include "stdafx.hpp"

#include "BufferObject.hpp"
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"

namespace hlx
{
	class VertexArray : public BufferObject
	{
	public:
		static std::shared_ptr<VertexArray> create();

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const;
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer) = 0;

		virtual const std::shared_ptr<ElementBuffer> getElementBuffer() const;
		virtual void setElementBuffer(const std::shared_ptr<ElementBuffer> buffer) = 0;

	protected:
		VertexArray() : m_vertexAttributeIndex{} {}

		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<ElementBuffer> m_elementBuffer;
		unsigned int m_vertexAttributeIndex;
	};
}
