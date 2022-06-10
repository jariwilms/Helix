#include "stdafx.hpp"
#include "Scene.hpp"

#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Scene/Entities/Base/Entity.hpp"
#include "Helix/Scene/Components/SpriteComponent.hpp"
#include "Helix/Scene/Components/TransformComponent.hpp"
#include "Helix/Scene/Components/TestComponent.hpp"

namespace hlx
{
	Scene::Scene()
	{
		m_registry = std::make_unique<EntityRegistry>();
		m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 3.0f } } };
		m_camera.setProjectionType(Projection::Type::Perspective);

		auto& e = m_entities.emplace_back(new Entity{ this });
		e->addComponent<SpriteComponent>();
	}

	void Scene::update(DeltaTime deltaTime)
	{
		m_camera.update(deltaTime);
	}

	void Scene::render()
	{
		Renderer::start(this);

		auto view = m_registry->view<SpriteComponent>();

		for (auto entity : view)
		{
			auto& component = m_registry->get<SpriteComponent>(entity);
			component.render();
		}

		Renderer::finish();
	}

	const hlx::Camera& Scene::getCamera() const
	{
		return m_camera;
	}

	EntityRegistry& Scene::getRegistry() const
	{
		return *m_registry;
	}

	const std::vector<std::shared_ptr<Entity>>& Scene::getEntities() const
	{
		return m_entities;
	}

	void Scene::destroyEntity(const Entity& entity)
	{
		auto lambda = [&](std::shared_ptr<Entity> element) -> bool { return element.get() == &entity; };
		auto it = std::find_if(m_entities.begin(), m_entities.end(), lambda);
		if (it != m_entities.end()) m_entities.erase(it);
	}
}
