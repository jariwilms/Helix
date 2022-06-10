#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/API/RenderAPI.hpp"
#include "Helix/Rendering/API/RenderBatch.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"
#include "Helix/Rendering/Objects/VertexBuffer.hpp"
#include "Helix/Rendering/Objects/ElementBuffer.hpp"
#include "Helix/Rendering/Shader.hpp"
#include "Helix/Rendering/Texture.hpp"

namespace hlx
{
	struct Vertex
	{
		Vertex() = default;
		~Vertex() = default;

		glm::vec3 position;
		glm::vec4 color;

		glm::vec2 textureCoordinate;
		float textureIndex;
		float textureScale;

		float entityId;
	};

	struct RenderBatch
	{
	public:
		RenderBatch(size_t bufferSize, size_t maxElements, const BufferLayout& layout)
			: vertexCount{}, elementCount{}
		{
			vao = VertexArray::create();
			vbo = VertexBuffer::create(bufferSize);
			ebo = ElementBuffer::create(maxElements);

			vbo->setLayout(layout);
			vao->setElementBuffer(ebo);
			vao->addVertexBuffer(vbo);

			vertexPtr = new Vertex[bufferSize];
			elementPtr = new unsigned int[maxElements];



			int slots{};
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &slots);
			textureSlots.resize(slots);

			textureSlots[0] = (Texture::create("textures/white.png"));
			shader = Shader::create("shaders/test.vert", "shaders/test.frag");
		}

		void bind()
		{
			vao->bind();

			for (int i = 0; i < textureCount; ++i)
				textureSlots.at(i)->bind(i);

			shader->bind();
		}

		void reset()
		{
			vao->unbind();
			shader->unbind();

			vertexCount = 0;
			elementCount = 0;
			textureCount = 1;
		}

		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<VertexBuffer> vbo;
		std::shared_ptr<ElementBuffer> ebo;

		Vertex* vertexPtr;
		size_t vertexCount;

		unsigned int* elementPtr;
		size_t elementCount;

		std::shared_ptr<Shader> shader;

		std::vector<std::shared_ptr<Texture>> textureSlots;
		size_t textureCount;
	};
}
