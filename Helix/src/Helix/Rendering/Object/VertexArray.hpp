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
		virtual ~VertexArray() {}

		static std::shared_ptr<VertexArray> create();

		inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return m_vertexBuffers; }
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer) = 0;

		inline const std::shared_ptr<ElementBuffer> getElementBuffer() const { return m_elementBuffer; }
		virtual void setElementBuffer(const std::shared_ptr<ElementBuffer> buffer) = 0;

	protected:
		VertexArray() : m_vertexAttributeIndex{} {}

		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<ElementBuffer> m_elementBuffer;

		unsigned int m_vertexAttributeIndex;
	};
}
