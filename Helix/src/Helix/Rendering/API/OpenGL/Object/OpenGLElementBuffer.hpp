#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Object/ElementBuffer.hpp"

namespace hlx
{
	class OpenGLElementBuffer : public ElementBuffer
	{
	public:
		OpenGLElementBuffer(unsigned int count, const unsigned int* data);
		~OpenGLElementBuffer() override;

		void bind() const override;
		void unbind() const override;
		bool isBound() const override;

		void setData(unsigned int count, const unsigned int* data) override;
		void setSubData(unsigned int count, const unsigned int* data) override;
		void setSubData(unsigned int count, unsigned int offset, const unsigned int* data) override;
	};
}
