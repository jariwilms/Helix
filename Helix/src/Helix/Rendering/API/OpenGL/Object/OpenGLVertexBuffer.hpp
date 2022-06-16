#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Object/VertexBuffer.hpp"

namespace hlx
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(size_t size, const float* data);
		~OpenGLVertexBuffer() override;
		
		void bind() const override;
		void unbind() const override;

		void resize(size_t size) override;
		void reset() override;

		void setBufferData(size_t size, const float* data) override;
	};
}
