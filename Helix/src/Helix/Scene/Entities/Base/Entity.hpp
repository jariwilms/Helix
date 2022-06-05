#pragma once

#include "stdafx.hpp"

#include "entt/entt.hpp"

#include "Helix/Scene/Components/Base/Component.hpp"

namespace hlx
{
	class Scene;

	class Entity
	{
	public:
		Entity(Scene* scene)
			: m_scene{ scene }
		{
			auto& registry = m_scene->getRegistry();
			m_id = registry.create();
		}
		virtual ~Entity()
		{
			auto& registry = m_scene->getRegistry();
			registry.destroy(m_id);
		}

		virtual void update()
		{
			for (auto& component : m_components)
				component->update();
		}

		virtual void render()
		{
			for (auto& component : m_components)
				component->render();
		}

		template<typename Component, typename... Args>
		Component& addComponent(Args... args)
		{
			auto& registry = m_scene->getRegistry();
			return registry.emplace<Component>(m_id, args);
		}

		template<typename Component>
		Component& getComponent()
		{
			auto& registry = m_scene->getRegistry();
			return registry.get<Component>(m_id)
		}

		template<typename Component>
		void removeComponent()
		{
			auto& registry = m_scene->getRegistry();
			registry.erase<Component>(m_id);
		}

	private:
		uint32_t m_id;
		Scene* m_scene;
		std::unordered_set<std::unique_ptr<Component>> m_components;
	};
}
