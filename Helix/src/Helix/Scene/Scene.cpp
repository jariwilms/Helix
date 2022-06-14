#include "stdafx.hpp"
#include "Scene.hpp"

namespace hlx
{
	Scene::Scene()
	{
		m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 3.0f } } };
		m_camera.setProjectionType(Projection::Type::Perspective);

		auto e1 = createEntity();
		auto e2 = createEntity();

		auto& c1 = addComponent<TransformComponent>(e1);
		c1.transform.translate(glm::vec3{ 0.4f, 0.0f, 0.0f });
		addComponent<SpriteComponent>(e1, "textures/kiryu.png");

		auto& c2 = addComponent<TransformComponent>(e2);
		c2.transform.translate(glm::vec3{ -0.4f, 0.0f, 0.0f });
		addComponent<SpriteComponent>(e2, "textures/missing.png");
	}

	void Scene::update(DeltaTime deltaTime)
	{
		m_camera.update(deltaTime);
	}

	void Scene::render()
	{
		auto view = m_registry.view<TransformComponent, SpriteComponent>();

		for (auto entity : view)
		{
			auto& transform = view.get<TransformComponent>(entity);
			auto& sprite = view.get<SpriteComponent>(entity);

			Renderer::renderQuad(transform, sprite.texture);
		}
	}
}
