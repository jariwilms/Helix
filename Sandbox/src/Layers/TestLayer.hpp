#pragma once

#include "entt/entt.hpp"

#include "Helix/Scene/Scene.hpp"

class TestLayer : public hlx::Layer
{
public:
	TestLayer() = default;

	void update() override
	{
		m_scene.update();
	}

	void render() override
	{
		m_scene.render();
	}

private:
	hlx::Scene m_scene;
};