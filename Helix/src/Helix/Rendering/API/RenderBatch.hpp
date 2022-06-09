#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Objects/BufferLayout.hpp"
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

	//TODO: platform agnostic -> only queries OpenGL API atm
	struct RenderBatch
	{
	public:
		RenderBatch(size_t bufferSize, size_t maxIndices, const BufferLayout& layout)
		{
			//vao = 


			//int slots{};
			//glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &slots);

			//textureSlots.reserve(slots);
		}

		void bind()
		{
			//vao->bind();


		}

		//std::shared_ptr<VertexArray> vao;
		//std::shared_ptr<VertexBuffer> vbo;
		//std::shared_ptr<ElementBuffer> ebo;

		//Vertex* vertexPtr;
		//size_t vertexCount;

		//unsigned int* elementPtr;
		//size_t elementCount;

		//std::shared_ptr<Shader> shader;

		//std::vector<std::shared_ptr<Texture>> textureSlots;
	};
}
