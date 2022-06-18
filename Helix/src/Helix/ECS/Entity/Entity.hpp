#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Scene;

	class Entity
	{
	public:
		Entity(uint32_t id, Scene* scene, Entity * parent = nullptr)
			: m_id{ id }, m_scene{ scene } { setName("Entity"); }

		uint32_t getId() const { return m_id; }
		const std::string& getName() const { return m_name; }
		const Scene* getScene() const { return m_scene; }

		inline void setName(const std::string& name) { m_name = name; }
		inline void setScene(Scene* scene) { m_scene = scene; }

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
		std::string m_name;

		Scene* m_scene;
	};
}
