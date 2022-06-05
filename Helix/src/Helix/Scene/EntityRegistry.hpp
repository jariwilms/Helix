#pragma once

#include "stdafx.hpp"

#include "entt/entt.hpp"

namespace hlx
{
	using uint32_t = entt::entity;

	class EntityRegistry
	{
	public:
		EntityRegistry() = default;
		~EntityRegistry() = default;

		uint32_t create()
		{
			return m_registry.create();
		}

		void destroy(uint32_t handle)
		{
			m_registry.destroy(handle);
		}

		template<typename... Component>
		bool has(uint32_t handle)
		{
			return m_registry.any_of<Component>(handle);
		}

		template<typename Component>
		Component& get(uint32_t handle)
		{
			return m_registry.get<Component>(handle);
		}

		template<typename Component, typename... Args>
		Component& emplace(uint32_t entity, Args... args)
		{
			return m_registry.emplace<Component>(entity, args);
		}

		template<typename Component>
		void erase(uint32_t handle)
		{
			return m_registry.erase<Component>(handle);
		}

		void clear()
		{
			m_registry.clear();
		}

	private:
		entt::registry m_registry;
	};
}
