#pragma once

#include "Helix/Rendering/Object/BufferObject.hpp"

namespace hlx
{
	class UniformBuffer : public BufferObject
	{
	public:
		virtual ~UniformBuffer() = default;

		static std::shared_ptr<UniformBuffer> create(unsigned int blockIndex, unsigned int blockBinding, size_t size, const void* data = nullptr);

		virtual void setData(size_t size, const void* data) = 0;
		virtual void setSubData(size_t size, const void* data) = 0;
		virtual void setSubData(size_t size, size_t offset, const void* data) = 0;

	protected:
		UniformBuffer(unsigned int blockIndex, unsigned int blockBinding) : m_blockIndex{ blockIndex }, m_blockBinding{ blockBinding }, m_dataSize{}, m_dataLimit{} {}

		unsigned int m_blockIndex;
		unsigned int m_blockBinding;
		static inline unsigned int s_boundUniformBufferId = 0;

		size_t m_dataSize;
		size_t m_dataLimit;
	};
}
