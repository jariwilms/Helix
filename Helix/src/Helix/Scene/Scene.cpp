#include "stdafx.hpp"
#include "Scene.hpp"

namespace hlx
{
	Scene::Scene()
	{
		m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 3.0f } } };
		m_camera.setProjectionType(Projection::Type::Perspective);

		auto& entity1 = createEntityDefault();
		auto& transform1 = entity1.getComponent<TransformComponent>();
		transform1.transform.translate(glm::vec3{ 0.4f, 0.0f, 0.0f });
		auto& sprite1 = entity1.addComponent<SpriteComponent>("textures/kiryu.png");

		auto& entity2 = createEntityDefault();
		auto& transform2 = entity2.getComponent<TransformComponent>();
		transform2.transform.translate(glm::vec3{ -0.4f, 0.0f, 0.0f });
		entity2.addComponent<SpriteComponent>("textures/missing.png");
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
