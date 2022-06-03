#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Objects/BufferObject.hpp"
#include "Helix/Rendering/Objects/BufferLayout.hpp"

namespace hlx
{
	class VertexBuffer : public BufferObject
	{
	public:
		static std::shared_ptr<VertexBuffer> create();
		static std::shared_ptr<VertexBuffer> create(float* data, int size);
		
		const BufferLayout& getLayout() const;
		virtual void setLayout(const BufferLayout& layout) = 0;

		virtual void setBufferData(float* data, int size) = 0;

	protected:
		VertexBuffer() = default;
		BufferLayout m_layout;
	};
}
