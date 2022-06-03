#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Objects/VertexBuffer.hpp"

namespace hlx
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* data, int size);
		~OpenGLVertexBuffer() override;
		
		void bind() const override;
		void unbind() const override;

		void setLayout(const BufferLayout& layout) override;

		void setBufferData(float* data, int size) override;
	};
}
