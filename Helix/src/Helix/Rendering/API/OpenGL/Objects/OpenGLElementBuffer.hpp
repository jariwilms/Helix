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
		OpenGLElementBuffer(size_t size, const unsigned int* data);
		~OpenGLElementBuffer() override;

		void bind() const override;
		void unbind() const override;

		virtual void resize(size_t size) override;
		virtual void reset() override;

		size_t getSize() const override;

		void setBufferData(size_t size, const unsigned int* data) override;
	};
}
