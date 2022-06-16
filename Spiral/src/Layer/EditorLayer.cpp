#include "stdafx.hpp"
#include "EditorLayer.hpp"

EditorLayer::EditorLayer()
	: m_scene{ new hlx::Scene{} } {}

void EditorLayer::update(DeltaTime deltaTime) 
{
	m_scene->update(deltaTime);

	m_renderStatisticsWidget.update();
	m_entityListWidget.update(m_scene);
	m_selectedEntityWidget.setSelectedEntity(m_entityListWidget.getSelectedEntity());

	m_sceneRenderWidget.update(deltaTime);
}

void EditorLayer::render() 
{
	//hlx::Renderer::start(m_scene->getCamera());
	//hlx::Renderer::poll();
	//m_scene->render();
	//hlx::Renderer::finish();
}

void EditorLayer::renderUI() 
{
	m_renderStatisticsWidget.renderUI();
	m_entityListWidget.renderUI();
	m_selectedEntityWidget.renderUI();

	m_sceneRenderWidget.renderUI(m_scene);
}

void EditorLayer::onEvent(hlx::Event& event) 
{
	auto lambda = [this](hlx::WindowCloseEvent& event) -> bool { hlx::Application::getInstance().popLayer(this); return true; };

	hlx::EventDispatcher dispatcher{ event };
	dispatcher.dispatch<hlx::WindowCloseEvent>(lambda);
}