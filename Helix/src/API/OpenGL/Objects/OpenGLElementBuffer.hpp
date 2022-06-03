#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Objects/ElementBuffer.hpp"

namespace hlx
{
	class OpenGLElementBuffer : public ElementBuffer
	{
	public:
		OpenGLElementBuffer(unsigned int* data, int size);
		~OpenGLElementBuffer() override;

		void bind() const override;
		void unbind() const override;

		int getSize() const override;

		void setBufferData(unsigned int* data, int size);
	};
}
