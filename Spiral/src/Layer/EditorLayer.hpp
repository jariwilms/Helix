#pragma once

#include <Helix.hpp>

#include "Helix/Widget/ContentBrowserWidget.hpp"
#include "Helix/Widget/EntityListWidget.hpp"
#include "Helix/Widget/RenderStatisticsWidget.hpp"
#include "Helix/Widget/SceneRenderWidget.hpp"
#include "Helix/Widget/SelectedEntityWidget.hpp"

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

	hlx::RenderStatisticsWidget m_renderStatisticsWidget;
	hlx::EntityListWidget m_entityListWidget;
	hlx::SelectedEntityWidget m_selectedEntityWidget;
	hlx::SceneRenderWidget m_sceneRenderWidget;
};
