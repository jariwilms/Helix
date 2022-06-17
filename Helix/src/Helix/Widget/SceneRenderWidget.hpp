#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Object/FrameBuffer.hpp"
#include "Helix/Rendering/RenderData.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Scene/Scene.hpp"
#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	class SceneRenderWidget : public Widget
	{
	public:
		SceneRenderWidget()
		{
			BufferLayout layout{};
			layout.addAttribute<float>(3);
			layout.addAttribute<float>(2);

			m_vao = VertexArray::create();
			m_vbo = VertexBuffer::create(sizeof(RenderData::FRAME_BUFFER_VERTICES), RenderData::FRAME_BUFFER_VERTICES);
			m_ebo = ElementBuffer::create(sizeof(RenderData::FRAME_BUFFER_ELEMENTS), RenderData::FRAME_BUFFER_ELEMENTS);

			m_vbo->setLayout(layout);
			m_vao->setElementBuffer(m_ebo);
			m_vao->addVertexBuffer(m_vbo);

			m_shader = Shader::create("shaders/framebuffer.vert", "shaders/framebuffer.frag");

			m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 3.0f } } };
			m_camera.setProjectionType(Projection::Type::Perspective);
		}
		~SceneRenderWidget() = default;

		void update(DeltaTime deltaTime) override
		{
			m_camera.update(deltaTime);
		}

		void renderUI(Scene* scene)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Scene");



			glm::uvec2 dimensions{ ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 19 };

			if (dimensions != lastWindowDimensions)
			{
				lastWindowDimensions = dimensions;

				glViewport(0, 0, dimensions.x, dimensions.y);
				m_camera.setScreenDimensions(dimensions);
			}

			m_frameBuffer = FrameBuffer::create(dimensions.x, dimensions.y);
			m_frameBuffer->bind();



			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			Renderer::start(m_camera);
			scene->render();
			Renderer::finish();

			m_frameBuffer->unbind();

			m_vao->bind();
			m_shader->bind();
			m_frameBuffer->bindTexture();

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			auto& texture = m_frameBuffer->getTexture();
			ImGui::Image((ImTextureID)texture->getId(), ImVec2((float)texture->getWidth(), (float)texture->getHeight()), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));



			ImGui::End();
			ImGui::PopStyleVar();
		}

	private:
		std::shared_ptr<VertexArray> m_vao;
		std::shared_ptr<VertexBuffer> m_vbo;
		std::shared_ptr<ElementBuffer> m_ebo;

		std::shared_ptr<FrameBuffer> m_frameBuffer;

		std::shared_ptr<Shader> m_shader;

		Camera m_camera;

		glm::uvec2 lastWindowDimensions;
	};
}
