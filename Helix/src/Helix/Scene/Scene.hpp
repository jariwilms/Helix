#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26819 26439 28020)
#include "entt/entt.hpp"
#pragma warning(default: 26819 26439 28020)

#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/Scene/Camera/Camera.hpp"
#include "Helix/ECS/Component/Components.hpp"

namespace hlx
{
	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		void update(DeltaTime deltaTime);
		void render();

		const Camera& getCamera() const { return m_camera; }

		Entity createEntity()
		{
			return m_entities.emplace_back((uint32_t)m_registry.create());
		}
		void destroyEntity(Entity entity)
		{
			auto ent = std::find_if(m_entities.begin(), m_entities.end(), [&](const Entity& _) { return _.getId() == entity.getId(); });
			if (ent != m_entities.end()) m_entities.erase(ent);

			m_registry.destroy((entt::entity)entity.getId());
		}
		Entity getEntity(size_t index) const
		{
			return m_entities.at(index);
		}
		std::vector<Entity>& getEntities()
		{
			return m_entities;
		}

		template<typename Component, typename... Args>
		Component& addComponent(Entity entity, Args&&... args)
		{
			return m_registry.emplace<Component>((entt::entity)entity.getId(), args...);
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
