#pragma once

#include "stdafx.hpp"

#include "Helix/Scene/Entities/EntityRegistry.hpp"
#include "Helix/Scene/Camera/Camera.hpp"

namespace hlx
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		void update();
		void render();

		const Camera& getCamera() const;

		EntityRegistry& getRegistry() const;
		const std::vector<std::shared_ptr<Entity>>& getEntities() const;

		template <typename T>
		Entity& createEntity()
		{
			auto& entity = m_entities.emplace(new Entity{ this });
			return *entity;
		}

		void destroyEntity(const Entity& entity);

	private:
		hlx::Camera m_camera;

		std::unique_ptr<EntityRegistry> m_registry;
		std::vector<std::shared_ptr<Entity>> m_entities;
	};
}
