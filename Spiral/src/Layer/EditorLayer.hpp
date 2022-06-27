#pragma once

#include <Helix.hpp>

#include "Helix/Widget/ContentBrowserWidget.hpp"
#include "Helix/Widget/SceneHierarchyWidget.hpp"
#include "Helix/Widget/RenderStatisticsWidget.hpp"
#include "Helix/Widget/SceneRenderWidget.hpp"
#include "Helix/Widget/EntityInspectorWidget.hpp"

class EditorLayer : public hlx::Layer
{
public:
	EditorLayer();
	~EditorLayer() = default;

	void update(DeltaTime deltaTime) override;
	void render() override;
	void renderUI() override;

	void onEvent(hlx::Event& event) override;

private:
	hlx::Scene* m_scene;

	hlx::ContentBrowserWidget m_contentBrowserWidget;
	hlx::RenderStatisticsWidget m_renderStatisticsWidget;
	hlx::SceneHierarchyWidget m_sceneHierarchyWidget;
	hlx::EntityInspectorWidget m_entityInspectorWidget;
	hlx::SceneRenderWidget m_sceneRenderWidget;
};
