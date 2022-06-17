#pragma once

#pragma warning(disable: 26819 26439 28020)
#include "entt/entt.hpp"
#pragma warning(default: 26819 26439 28020)

#include "Helix/ECS/Component/Components.hpp"
#include "Helix/ECS/Entity/Entity.hpp"

namespace hlx
{
	class Registry
	{
	using globalIdentifier = uint32_t;
	using localIdentifier = entt::entity;

	public:
		Registry() = default;
		~Registry() = default;

		globalIdentifier createEntity()
		{
			return castToGlobalIdentifier(m_registry.create());
		}
		void destroyEntity(const Entity& entity)
		{
			m_registry.destroy(castToRegistryIdentifier(entity));
		}

		template<typename Component, typename... Args>
		Component& addComponent(const Entity& entity, Args&&... args)
		{
			return m_registry.emplace<Component>(castToRegistryIdentifier(entity), args...);
		}
		template<typename Component>
		bool hasComponent(const Entity& entity)
		{
			return m_registry.any_of<Component>(castToRegistryIdentifier(entity));
		}
		template<typename Component>
		Component& getComponent(const Entity& entity)
		{
			return m_registry.get<Component>(castToRegistryIdentifier(entity));
		}
		template<typename Component>
		void removeComponent(const Entity& entity)
		{
			m_registry.remove<Component>(castToRegistryIdentifier(entity));
		}

		template<typename Component, typename... Other, typename... Exclude>
		entt::basic_view<entt::entity, entt::get_t<Component, Other...>, entt::exclude_t<Exclude...>> view(entt::exclude_t<Exclude...> = {}) 
		{
			return m_registry.view<Component, Other..., Exclude...>(); //ik snap er geen kak van lol

			//ja bro return gewoon 
			//entt::basic_view<entt::entity<entt::registry<entt::identifier<entt::exclude_list...<entt::exclude_t::options::opt...>>>, entt::entity<T identifier>>();
			//totaal niet confusing
		}
		template<typename... Owned, typename... Exclude>
		entt::basic_group<entt::entity, entt::owned_t<Owned...>, entt::get_t<>, entt::exclude_t<Exclude...>> group(entt::exclude_t<Exclude...> = {})
		{
			return m_registry.group<Owned...>();
		}

	private:
		globalIdentifier castToGlobalIdentifier(entt::entity entity) { return static_cast<globalIdentifier>(entity); }
		localIdentifier castToRegistryIdentifier(const Entity& entity) { return static_cast<localIdentifier>(entity.getId()); }

		entt::registry m_registry;
	};
}
