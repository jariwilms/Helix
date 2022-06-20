#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class ElementBuffer : public BufferObject
	{
	public:
		virtual ~ElementBuffer() = default;

		static std::shared_ptr<ElementBuffer> create(size_t size, const unsigned int* data = nullptr);

		inline size_t getSize() const { return m_bufferSize; }

		virtual void setBufferData(size_t size, const unsigned int* data) = 0;

	protected:
		ElementBuffer() : m_bufferSize{} {}

		size_t m_bufferSize;
	};
}
