#pragma once

#include "stdafx.hpp"

#pragma warning(disable: 26819 26439)
#include "entt/entt.hpp"
#pragma warning(default: 26819 26439)

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
		Component& emplace(uint32_t entity, Args&&... args)
		{
			return m_registry.get_or_emplace<Component>(entity, std::forward<Args>(args)...);
		}

		template<typename Component>
		void erase(uint32_t handle)
		{
			return m_registry.erase<Component>(handle);
		}

		template<typename Component, typename... Other, typename... Exclude>
		entt::basic_view<entt::entity, entt::get_t<std::add_const_t<Component>, std::add_const_t<Other>...>, entt::exclude_t<Exclude...>> view(entt::exclude_t<Exclude...> = {}) const 
		{
			return m_registry.view<Component, Other..., Exclude...>();
		}

		template<typename... Owned, typename... Exclude>
		entt::basic_group<entt::entity, entt::owned_t<Owned...>, entt::get_t<>, entt::exclude_t<Exclude...>> group(entt::exclude_t<Exclude...> = {}) 
		{
			return m_registry.group<Owned...>();
		}

		void clear()
		{
			m_registry.clear();
		}

	private:
		entt::registry m_registry;
	};
}
