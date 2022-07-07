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
		static inline unsigned int getBoundObjectId() { return s_boundVertexArrayId; }

		inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return m_vertexBuffers; }
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer) = 0;

		inline const std::shared_ptr<ElementBuffer> getElementBuffer() const { return m_elementBuffer; }
		virtual void setElementBuffer(const std::shared_ptr<ElementBuffer> buffer) = 0;

	protected:
		VertexArray() : m_vertexAttributeIndex{} { s_boundVertexArrayId = 0; }

		static inline unsigned int s_boundVertexArrayId;

		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<ElementBuffer> m_elementBuffer;

		unsigned int m_vertexAttributeIndex;
	};
}
