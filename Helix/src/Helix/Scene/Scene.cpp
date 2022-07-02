#include "stdafx.hpp"
#include "Scene.hpp"

namespace hlx
{
	Scene::Scene()
	{
		m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 3.0f } } };
		m_camera.setProjectionType(Projection::Type::Perspective);

		auto& entity1 = createEntityDefault();
		entity1.setEnabled(false);
		auto& transform1 = entity1.getComponent<TransformComponent>();
		transform1.transform.translate(glm::vec3{ 0.4f, 0.0f, 0.0f });
		auto& sprite1 = entity1.addComponent<SpriteComponent>("textures/kiryu.png");

		auto& entity2 = createEntityDefault();
		entity2.setEnabled(false);
		auto& transform2 = entity2.getComponent<TransformComponent>();
		transform2.transform.translate(glm::vec3{ -0.4f, 0.0f, 0.0f });
		entity2.addComponent<SpriteComponent>("textures/checkerboard.png");

		auto& entity3 = createEntityDefault();
		auto& model = entity3.addComponent<ModelComponent>("models/backpack/backpack.obj");
	}

	void Scene::update(DeltaTime deltaTime)
	{
		m_camera.update(deltaTime);
	}

	void Scene::render()
	{
		auto spriteView = m_registry.view<TransformComponent, SpriteComponent>();

		for (auto id : spriteView)
		{
			auto& entity = m_registry.getEntity((uint32_t)id);
			if (!entity.isEnabled()) continue;

			auto& transform = spriteView.get<TransformComponent>(id);
			auto& sprite = spriteView.get<SpriteComponent>(id);

			Renderer::renderQuad(transform, sprite.texture);
		}

		auto modelView = m_registry.view<TransformComponent, ModelComponent>();

		for (auto id : modelView)
		{
			auto& entity = m_registry.getEntity((uint32_t)id);
			if (!entity.isEnabled()) continue;

			auto& transform = modelView.get<TransformComponent>(id);
			auto& modelComponent = modelView.get<ModelComponent>(id);

			Renderer::renderModel(*modelComponent.model, transform);
		}
	}
}
