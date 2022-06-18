#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Component/Components.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/ECS/Registry.hpp"
#include "Helix/Scene/Camera/Camera.hpp"

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

		Entity& createEntity()
		{
			Entity entity = Entity{ m_registry.createEntity(), this };
			return m_entities.emplace_back(std::move(entity));
		}
		Entity& createEntityDefault()
		{
			auto& entity = createEntity();
			entity.addComponent<TransformComponent>();

			return entity;
		}
		void destroyEntity(const Entity& entity)
		{
			m_registry.destroyEntity(entity);

			auto it = std::find_if(m_entities.begin(), m_entities.end(), [&](const Entity& _) { return _.getId() == entity.getId(); });
			if (it != m_entities.end()) m_entities.erase(it); 
			else HLX_CORE_ERROR("The given entity was not found: {0}", entity.getId());
		}
		Entity& getEntity(size_t index)
		{
			 if (index > -1 && index < m_entities.size()) return m_entities.at(index);
			 HLX_CORE_ERROR("Given entity index is out of range: {0}", index);
		}
		std::vector<Entity>& getEntities()
		{
			return m_entities;
		}

		Registry& getRegistry() { return m_registry; }

	private:
		Camera m_camera;

		Registry m_registry;
		std::vector<Entity> m_entities;
	};
}
