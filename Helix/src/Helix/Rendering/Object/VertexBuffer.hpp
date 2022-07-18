#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Data/Vertex.hpp"
#include "Helix/Rendering/Data/MeshVertex.hpp"
#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/Object/BufferLayout.hpp"

namespace hlx
{
	template <typename T>
	class VertexBuffer : public BufferObject
	{
	public:
		virtual ~VertexBuffer() = default;

		static std::shared_ptr<VertexBuffer<T>> create(unsigned int count, const float* data = nullptr);

		static inline unsigned int getBoundObjectId() { return s_boundVertexBufferId; }

		inline size_t getSize() const { return static_cast<size_t>(m_dataCount) * sizeof(float); }
		inline unsigned int getCount() const { return m_dataCount; }

		virtual void setData(unsigned int count, const float* data) = 0;
		virtual void setSubData(unsigned int count, const float* data) = 0;
		virtual void setSubData(unsigned int count, unsigned int offset, const float* data) = 0;

		inline BufferLayout& getLayout() { return m_layout; }
		inline void setLayout(const BufferLayout& layout) { m_layout = layout; }

	protected:
		VertexBuffer() : m_dataCount{}, m_dataLimit{}, m_typeSize{ sizeof(T) } {}

		static inline unsigned int s_boundVertexBufferId = 0;

		unsigned int m_dataCount;
		unsigned int m_dataLimit;
		size_t m_typeSize;
		
		BufferLayout m_layout;
	};
}
