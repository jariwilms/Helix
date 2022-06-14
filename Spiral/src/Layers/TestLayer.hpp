#pragma once

#include <Helix.hpp>

#include "entt/entt.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/core/Application.hpp"
#include "Helix/Core/DeltaTime.hpp"
#include "Helix/Event/Base/Event.hpp"
#include "Helix/Event/WindowEvent.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Scene/Scene.hpp"
#include "Helix/Widget/RenderStatisticsWidget.hpp"

class TestLayer : public hlx::Layer
{
public:
	TestLayer()
	{

	}

	void update(DeltaTime deltaTime) override
	{
		m_scene.update(deltaTime);
	}

	void render() override
	{
		hlx::Renderer::start(m_scene.getCamera());
		hlx::Renderer::poll();

		m_scene.render();

		auto& statistics = hlx::Renderer::measure();
		hlx::Renderer::finish();



		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();

		//RenderStatisticsWidget::show(statistics);

		//auto& entities = m_scene.getEntities();
		//static hlx::Entity* selectedEntity = nullptr;

		//ImGui::Begin("Entities");
		//
		//if (ImGui::Button("Create"))
		//{
		//	m_scene.createEntity();
		//	selectedEntity = nullptr;
		//}

		//for (int i = 0; i < entities.size(); ++i)
		//{
		//	std::string v = std::to_string(i) + ". " + std::to_string(entities.at(i).getId());
		//	if (ImGui::Selectable(v.c_str()))
		//	{
		//		selectedEntity = &entities.at(i);
		//	}
		//}

		//ImGui::End();



		//ImGui::Begin("Selected");
		//if (selectedEntity != nullptr)
		//{
		//	std::string ent = "Id: " + std::to_string(selectedEntity->getId());
		//	ImGui::Text(ent.c_str());
		//}
		//else ImGui::Text("Nothing selected");
		//ImGui::End();



		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void onEvent(hlx::Event& event) override
	{
		auto lambda = [this](hlx::WindowCloseEvent& event) -> bool { hlx::Application::getInstance().popLayer(this); return true; };

		hlx::EventDispatcher dispatcher{ event };
		dispatcher.dispatch<hlx::WindowCloseEvent>(lambda);
	}

private:
	hlx::Scene m_scene;
};