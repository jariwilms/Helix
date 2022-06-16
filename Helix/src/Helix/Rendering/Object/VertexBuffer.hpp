#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Object/BufferObject.hpp"
#include "Helix/Rendering/Object/BufferLayout.hpp"

namespace hlx
{
	class VertexBuffer : public BufferObject
	{
	public:
		virtual ~VertexBuffer() {}

		static std::shared_ptr<VertexBuffer> create(size_t size, const float* data = nullptr);
		
		inline size_t getSize() const { return m_bufferSize; }

		inline virtual const BufferLayout& getLayout() const { return m_layout; }
		inline virtual void setLayout(const BufferLayout& layout) { m_layout = layout; }

		virtual void setBufferData(size_t size, const float* data) = 0;

	protected:
		VertexBuffer() : m_bufferSize{} {}

		BufferLayout m_layout;
		size_t m_bufferSize;
	};
}
