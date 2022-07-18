#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/API/RendererAPI.hpp"
#include "Helix/Rendering/Object/VertexArray.hpp"
#include "Helix/Rendering/Object/VertexBuffer.hpp"
#include "Helix/Rendering/Object/ElementBuffer.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Data/Vertex.hpp"

namespace hlx
{
	template <typename T>
	struct RenderBatch
	{
	public:
		RenderBatch(unsigned int count, const BufferLayout& layout) 
			: vertexCount{}, elementCount{}, textureCount{ 1 }
		{
			vao = VertexArray<T>::create();
			vbo = VertexBuffer<T>::create(count, nullptr);
			ebo = ElementBuffer::create(count);

			vbo->setLayout(layout);
			vao->setElementBuffer(ebo);
			vao->addVertexBuffer(vbo);

			vertices.resize(count);
			elements.resize(count);



			unsigned int offset{};
			constexpr int indicesPerQuad = 6;
			constexpr int offsetPerTriangle = 4;

			for (size_t i{ 0 }; i < static_cast<size_t>(count - 6); i += indicesPerQuad, offset += offsetPerTriangle)
			{
				elements.at(i + 0) = offset + 0;
				elements.at(i + 1) = offset + 1;
				elements.at(i + 2) = offset + 2;
				
				elements.at(i + 3) = offset + 0;
				elements.at(i + 4) = offset + 2;
				elements.at(i + 5) = offset + 3;
			}

			int slots{};
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &slots);
			textureSlots.resize(slots);

			textureSlots[0] = (Texture::create("textures/white.png"));
			shader = Shader::create("shaders/default2.glsl");
		}

		void bind()
		{
			vao->bind();
			shader->bind();

			for (int i{ 0 }; i < textureCount; ++i)
				textureSlots.at(i)->bindUnit(i);
		}

		void reset()
		{
			vertexCount = 0;
			elementCount = 0;
			textureCount = 1;
		}

		std::shared_ptr<VertexArray<T>> vao;
		std::shared_ptr<VertexBuffer<T>> vbo;
		std::shared_ptr<ElementBuffer> ebo;

		std::vector<Vertex> vertices; //fix?
		unsigned int vertexCount;

		std::vector<unsigned int> elements;
		unsigned int elementCount;

		std::shared_ptr<Shader> shader;

		std::vector<std::shared_ptr<Texture>> textureSlots;
		size_t textureCount; //Todo: unsigned int
	};
}
