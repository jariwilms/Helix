#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/Object/BufferLayout.hpp"
#include "Helix/Rendering/Object/VertexBuffer.hpp"
#include "Helix/Rendering/Object/ElementBuffer.hpp"

namespace hlx
{
	class VertexArray : public BufferObject
	{
	public:
		virtual ~VertexArray() = default;

		static std::shared_ptr<VertexArray> create();

		inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return m_vertexBuffers; }
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer) = 0;

		inline const std::shared_ptr<ElementBuffer> getElementBuffer() const { return m_elementBuffer; }
		virtual void setElementBuffer(const std::shared_ptr<ElementBuffer> buffer) = 0;

	protected:
		VertexArray() : m_vertexAttributeIndex{} {}

		unsigned int m_vertexAttributeIndex;

		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<ElementBuffer> m_elementBuffer;
	};
}
