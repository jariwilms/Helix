#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Scene;

	class Entity
	{
	public:
		Entity(uint32_t id, Scene* scene, Entity* parent = nullptr)
			: m_id{ id }, m_scene{ scene } {}

		uint32_t getId() const { return m_id; }
		const Scene* getScene() const { return m_scene; }

		template<typename Component, typename... Args>
		Component& addComponent(Args&&... args)
		{
			return m_scene->getRegistry().addComponent<Component>(*this, args...);
		}
		template<typename Component>
		bool hasComponent()
		{
			return m_scene->getRegistry().hasComponent<Component>(*this);
		}
		template<typename Component>
		Component& getComponent()
		{
			return m_scene->getRegistry().getComponent<Component>(*this);
		}
		template<typename Component>
		void removeComponent()
		{
			m_scene->getRegistry().removeComponent<Component>(*this);
		}

	private:
		uint32_t m_id;
		Scene* m_scene;
	};
}
