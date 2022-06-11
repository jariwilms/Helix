#pragma once

#include <Helix.hpp>

#include "entt/entt.hpp"

#include "Helix/Scene/Scene.hpp"

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
		m_scene.render();
	}

private:
	hlx::Scene m_scene;
};