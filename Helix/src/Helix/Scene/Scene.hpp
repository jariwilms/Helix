#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26819 26439)
#include "entt/entt.hpp"
#pragma warning(default: 26819 26439)

#include "Helix/Scene/Camera/Camera.hpp"
#include "Helix/ECS/Component/Components.hpp"

namespace hlx
{
	using Entity = uint32_t;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		void update(DeltaTime deltaTime);
		void render();

		const Camera& getCamera() const;

		Entity Scene::createEntity()
		{
			return (uint32_t)m_registry.create();
		}
		void Scene::destroyEntity(Entity entity)
		{
			m_registry.destroy((entt::entity)entity);
		}

		template<typename Component, typename... Args>
		Component& addComponent(Entity entity, Args&&... args)
		{
			return m_registry.emplace<Component>((entt::entity)entity, args...);
		}
		template<typename Component>
		Component& getComponent(Entity entity)
		{
			return m_registry.get<Component>(entity);
		}
		template<typename Component>
		void removeComponent(Entity entity)
		{
			m_registry.remove<Component>(entity);
		}

	private:
		Camera m_camera;

		entt::registry m_registry;
		std::vector<Entity> m_entities;
	};
}
