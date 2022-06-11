#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Object/VertexArray.hpp"

namespace hlx
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void bind() const override;
		void unbind() const override;

		void addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer) override;
		void setElementBuffer(const std::shared_ptr<ElementBuffer> buffer) override;
	};
}
