#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Scene;

	class Entity
	{
	public:
		Entity(uint32_t id, Scene* scene, Entity* parent = nullptr, std::string name = "Entity")
			: m_id{ id }, m_name{ name }, m_scene{ scene }, m_enabled{ true } {}

		inline uint32_t getId() const { return m_id; }
		inline const std::string& getName() const { return m_name; }
		inline const Scene* getScene() const { return m_scene; }
		inline bool isEnabled() const { return m_enabled; }

		inline void setName(const std::string& name) { m_name = name; }
		inline void setScene(Scene* scene) { m_scene = scene; }
		inline void setEnabled(bool state) { m_enabled = state; }

		template<typename Component, typename... Args>
		Component& addComponent(Args&&... args)
		{
			return m_scene->m_registry.addComponent<Component>(*this, args...);
		}
		template<typename Component>
		bool hasComponent()
		{
			return m_scene->m_registry.hasComponent<Component>(*this);
		}
		template<typename Component>
		Component& getComponent()
		{
			return m_scene->m_registry.getComponent<Component>(*this);
		}
		template<typename Component>
		void removeComponent()
		{
			m_scene->m_registry.removeComponent<Component>(*this);
		}

	private:
		uint32_t m_id;
		std::string m_name;
		
		Scene* m_scene;

		bool m_enabled;
	};
}
