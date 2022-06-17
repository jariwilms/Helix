#include "stdafx.hpp"
#include "EditorLayer.hpp"

EditorLayer::EditorLayer()
	: m_scene{ new hlx::Scene{} }
{
	m_entityListWidget.setScene(m_scene);
}

void EditorLayer::update(DeltaTime deltaTime) 
{
	m_scene->update(deltaTime);

	m_contentBrowserWidget.update(deltaTime);
	m_renderStatisticsWidget.update(deltaTime);
	m_entityListWidget.update(deltaTime);
	m_sceneRenderWidget.update(deltaTime);
}

void EditorLayer::render() 
{

}

void EditorLayer::renderUI() 
{
	m_contentBrowserWidget.renderUI();

	m_renderStatisticsWidget.renderUI();
	m_entityListWidget.renderUI();

	m_selectedEntityWidget.setSelectedEntity(m_entityListWidget.getSelectedEntity());
	m_selectedEntityWidget.renderUI();

	m_sceneRenderWidget.renderUI(m_scene);
}

void EditorLayer::onEvent(hlx::Event& event) 
{
	auto lambda = [this](hlx::WindowCloseEvent& event) -> bool { hlx::Application::getInstance().popLayer(this); return true; };

	hlx::EventDispatcher dispatcher{ event };
	dispatcher.dispatch<hlx::WindowCloseEvent>(lambda);
}