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
		//Scene(const Scene& other)
		//{
		//	m_camera = other.getCamera();
		//	m_registry = other.m_registry;
		//}
		~Scene() = default;

		void update(DeltaTime deltaTime);
		void render();

		const Camera& getCamera() const { return m_camera; }

		Entity& createEntity()
		{
			return m_registry.createEntity(this);
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
		}
		Entity& getEntity(uint32_t id) 
		{ 
			return m_registry.getEntity(id); 
		}
		std::vector<Entity>& getEntities()
		{
			return m_registry.getEntities();
		}

	private:
		Camera m_camera;
		Registry m_registry;

		friend class Entity;
	};
}
