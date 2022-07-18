#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/Object/BufferLayout.hpp"
#include "Helix/Rendering/Object/VertexBuffer.hpp"
#include "Helix/Rendering/Object/ElementBuffer.hpp"

namespace hlx
{
	template <typename T>
	class VertexArray : public BufferObject
	{
	public:
		virtual ~VertexArray() = default;

		static std::shared_ptr<VertexArray<T>> create();
		
		static inline unsigned int getBoundObjectId() { return s_boundVertexArrayId; }

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer<T>> buffer) = 0;
		inline const std::vector<std::shared_ptr<VertexBuffer<T>>>& getVertexBuffers() const { return m_vertexBuffers; }

		inline const std::shared_ptr<ElementBuffer> getElementBuffer() const { return m_elementBuffer; }
		virtual void setElementBuffer(const std::shared_ptr<ElementBuffer> buffer) = 0;

	protected:
		VertexArray() : m_vertexAttributeIndex{} {}

		static inline unsigned int s_boundVertexArrayId = 0;

		std::vector<std::shared_ptr<VertexBuffer<T>>> m_vertexBuffers;
		std::shared_ptr<ElementBuffer> m_elementBuffer;

		unsigned int m_vertexAttributeIndex;
	};
}
