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
		static std::shared_ptr<VertexBuffer> create();
		static std::shared_ptr<VertexBuffer> create(size_t size, const float* data = nullptr);
		
		const BufferLayout& getLayout() const;
		virtual void setLayout(const BufferLayout& layout) = 0;

		virtual void setBufferData(size_t size, const float* data) = 0;

	protected:
		VertexBuffer() : m_bufferSize{} {}
		VertexBuffer(size_t size) : m_bufferSize{ size } {}

		BufferLayout m_layout;
		size_t m_bufferSize;
	};
}
