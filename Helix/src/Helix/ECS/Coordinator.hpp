#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Registry.hpp"
#include "Helix/ECS/Network.hpp"

namespace hlx
{
	class Coordinator
	{
	public:
		Coordinator()
		{
			m_registry = std::make_unique<Registry>();
			m_systemManager = std::make_unique<Network>();
		}
		~Coordinator() = default;

		template <typename System>
		std::shared_ptr<System> registerSystem()
		{
			return m_systemManager->registerSystem<System>();
		}

		Entity createEntity()
		{
			return m_registry->createEntity();
		}

		void destroyEntity(Entity entity)
		{
			m_registry->destroyEntity(entity);
		}

		template <typename Component>
		Component& addComponent(Entity entity)
		{
			return m_registry->addComponent<Component>(entity);
		}

		template <typename Component>
		bool hasComponent(Entity entity)
		{
			return m_registry->hasComponent<Component>(entity);
		}

		template <typename Component>
		Component& getComponent(Entity entity)
		{
			return m_registry->getComponent<Component>(entity);
		}

		template <typename Component>
		void removeComponent(Entity entity)
		{
			m_registry->removeComponent<Component>(entity);
		}

	private:
		std::unique_ptr<Registry> m_registry;
		std::unique_ptr<Network> m_systemManager;
	};
}
