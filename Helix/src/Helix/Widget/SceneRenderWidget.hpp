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

			m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 10.0f } } };
			m_camera.setProjectionType(Projection::Type::Perspective);
		}
		~SceneRenderWidget() = default;

		void update(DeltaTime deltaTime) override
		{
			if (isFocused())
			{
				Input::setMouseLock(Input::isButtonPressed(Button::ButtonRight));
				m_camera.update(deltaTime);
			}
			else
			{
				Input::setMouseLock(false);
			}
		}

		void renderUI(Scene* scene)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Scene");

			auto windowPosition = *(glm::vec2*)&ImGui::GetWindowPos();
			auto windowSize = *(glm::vec2*)&ImGui::GetWindowSize();
			auto& cursorPosition = Input::getCursorPosition();

			if (Input::isButtonPressedOnce(Button::ButtonRight))
			{
				if (cursorPosition.x > windowPosition.x && cursorPosition.x < windowPosition.x + windowSize.x &&
					cursorPosition.y > windowPosition.y && cursorPosition.y < windowPosition.y + windowSize.y &&
					Input::isButtonPressed(Button::ButtonRight)) ImGui::SetWindowFocus();
			}

			setFocused(ImGui::IsWindowFocused());

			auto dim = ImGui::GetContentRegionAvail();
			glm::uvec2 dimensions{ static_cast<unsigned int>(dim.x), static_cast<unsigned int>(dim.y) };

			if (dimensions != lastWindowDimensions)
			{
				lastWindowDimensions = dimensions;

				glViewport(0, 0, dimensions.x, dimensions.y);
				m_camera.setScreenDimensions(dimensions);
			}

			m_frameBuffer = FrameBuffer::create(dimensions.x, dimensions.y);
			m_frameBuffer->bind();

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
			glEnable(GL_DEPTH_TEST);



			Renderer::start(m_camera);
			scene->render();
			Renderer::finish();



			m_frameBuffer->unbind();
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);



			m_vao->bind();
			m_shader->bind();
			m_frameBuffer->bindTexture();

			glDisable(GL_DEPTH_TEST);
			glDrawArrays(GL_TRIANGLES, 0, 6);



			ImGui::Image((ImTextureID)((size_t)m_frameBuffer->getTexture()->getId()), ImVec2((float)dimensions.x, (float)dimensions.y), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

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
