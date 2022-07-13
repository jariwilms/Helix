#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/RenderContext.hpp"
#include "Helix/Rendering/Object/FrameBuffer.hpp"
#include "Helix/Rendering/Data/RenderData.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Scene/Scene.hpp"
#include "Helix/Widget/Base/Widget.hpp"

namespace hlx
{
	class SceneRenderWidget : public Widget
	{
	public:
		SceneRenderWidget()
			: m_rasterizationMode{}, m_lastRasterizationMode {}
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

			m_shader = Shader::create("shaders/framebuffer.glsl");

			m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 10.0f } } };
			auto persp = m_camera.getPerspectiveProjectionSettings();
			persp.farPlane = 1000.0f;
			m_camera.setPerspectiveProjectionSettings(persp);
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
			if (!isEnabled())
				return;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Scene", (bool*)nullptr, ImGuiWindowFlags_MenuBar);



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

			if (dimensions != m_lastWindowDimensions)
			{
				m_lastWindowDimensions = dimensions;

				glViewport(0, 0, dimensions.x, dimensions.y);
				m_camera.setScreenDimensions(dimensions);
			}



			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Options"))
				{
					ImGui::Combo("Rasterization", &m_rasterizationMode, "Fill\0Line\0Point\0\0");

					if (m_rasterizationMode != m_lastRasterizationMode)
					{
						switch (m_rasterizationMode)
						{
							case 0: RenderContext::setRasterizationMode(RasterizationFunction::Fill);			break;
							case 1: RenderContext::setRasterizationMode(RasterizationFunction::Line);			break;
							case 2: RenderContext::setRasterizationMode(RasterizationFunction::Point);			break;
								
							default:																			break;
						}
					}

					m_lastRasterizationMode = m_rasterizationMode;
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}


			
			FrameBufferBlueprint frameBufferBlueprint{dimensions};
			auto& textureBlueprint = frameBufferBlueprint.addTextureBlueprint();
			auto& renderBufferBlueprint = frameBufferBlueprint.addRenderBufferBlueprint();
			
			m_frameBuffer = FrameBuffer::create(frameBufferBlueprint);
			m_frameBuffer->bind();

			Renderer::setClearColor({ glm::vec3{ 0.1f }, 1.0f });
			Renderer::clearBuffer(BufferComponent::Color | BufferComponent::Depth);

			RenderContext::enable(RenderFunction::DepthTest);



			Renderer::start(m_camera);
			scene->render();
			Renderer::finish();



			m_frameBuffer->unbind();
			Renderer::setClearColor(glm::vec4{ 1.0f });
			Renderer::clearBuffer(BufferComponent::Color);
			
			m_vao->bind();
			m_shader->bind();
			m_frameBuffer->bindTextures();

			RenderContext::disable(RenderFunction::DepthTest);
			glDrawArrays(GL_TRIANGLES, 0, 6);//fix


			
			ImGui::Image((ImTextureID)((size_t)m_frameBuffer->getTextures()[0]->getId()), ImVec2((float)dimensions.x, (float)dimensions.y), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

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

		glm::uvec2 m_lastWindowDimensions;

		int m_rasterizationMode;
		int m_lastRasterizationMode;
	};
}
