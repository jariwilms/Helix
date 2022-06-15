#pragma once

#include <Helix.hpp>

#include "entt/entt.hpp"


#include "Helix/Core/Application.hpp"
#include "Helix/Core/DeltaTime.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/Event/Base/Event.hpp"
#include "Helix/Event/WindowEvent.hpp"
#include "Helix/Rendering/Renderer/Renderer.hpp"
#include "Helix/Scene/Scene.hpp"
#include "Helix/Widget/RenderStatisticsWidget.hpp"
#include "Helix/Widget/EntityListWidget.hpp"
#include "Helix/Widget/SelectedEntityWidget.hpp"

class TestLayer : public hlx::Layer
{
public:
	TestLayer()
	{
		m_scene = new hlx::Scene{};
	}

	void update(DeltaTime deltaTime) override
	{
		m_scene->update(deltaTime);
		m_renderStatisticsWidget.update();
		m_entityListWidget.update(m_scene);
		m_selectedEntityWidget.setSelectedEntity(m_entityListWidget.getSelectedEntity());
	}

	void render() override
	{
		hlx::Renderer::start(m_scene->getCamera());
		hlx::Renderer::poll();

		m_scene->render();

		hlx::Renderer::finish();
	}

	void renderUI() override
	{
		m_renderStatisticsWidget.renderUI();
		m_entityListWidget.renderUI();
		m_selectedEntityWidget.renderUI();
	}

	void onEvent(hlx::Event& event) override
	{
		auto lambda = [this](hlx::WindowCloseEvent& event) -> bool { hlx::Application::getInstance().popLayer(this); return true; };

		hlx::EventDispatcher dispatcher{ event };
		dispatcher.dispatch<hlx::WindowCloseEvent>(lambda);
	}

private:
	hlx::Scene* m_scene;

	hlx::RenderStatisticsWidget m_renderStatisticsWidget;
	hlx::EntityListWidget m_entityListWidget;
	hlx::SelectedEntityWidget m_selectedEntityWidget;
};
