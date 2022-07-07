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

		static std::shared_ptr<ElementBuffer> create(unsigned int count, const unsigned int* data = nullptr);
		static inline unsigned int getBoundObjectId() { return s_boundElementBufferId; }

		inline size_t getSize() const { return static_cast<size_t>(m_dataCount) * sizeof(unsigned int); }
		inline unsigned int getCount() const { return m_dataCount; }

		virtual void setData(unsigned int count, const unsigned int* data) = 0;
		virtual void setSubData(unsigned int count, const unsigned int* data) = 0;
		virtual void setSubData(unsigned int count, unsigned int offset, const unsigned int* data) = 0;

	protected:
		ElementBuffer() : m_dataCount{}, m_dataLimit{} { s_boundElementBufferId = 0; }

		static inline unsigned int s_boundElementBufferId;

		unsigned int m_dataCount;
		unsigned int m_dataLimit;
	};
}
