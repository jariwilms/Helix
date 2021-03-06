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

		Entity& createEntity(Scene* scene)
		{
			auto id = static_cast<globalIdentifier>(m_registry.create());
			auto name = "Entity" + std::to_string(id);
			auto& entity = m_entities.emplace_back(id, scene, nullptr, name);

			return entity;
		}
		void destroyEntity(const Entity& entity)
		{
			m_registry.destroy(castToRegistryIdentifier(entity));

			auto it = std::find_if(m_entities.begin(), m_entities.end(), [&](const Entity& _) -> bool { return _.getId() == entity.getId(); });
			if (it != m_entities.end()) m_entities.erase(it);
			else HLX_CORE_ERROR("The given entity was not found: {0}", entity.getId());
		}

		template<typename Component, typename... Args>
		Component& addComponent(const Entity& entity, Args&&... args)
		{
			if (hasComponent<Component>(entity)) HLX_CORE_WARNING("Entity {0} already has component, returning existing", entity.getId());
			return m_registry.get_or_emplace<Component>(castToRegistryIdentifier(entity), args...);
		}
		template<typename... Component>
		bool hasComponent(const Entity& entity)
		{
			return m_registry.any_of<Component...>(castToRegistryIdentifier(entity));
		}
		template<typename Component>
		Component& getComponent(const Entity& entity)
		{
			if (!hasComponent<Component>(entity)) HLX_CORE_CRITICAL("Entity {0} does not have component", entity.getId());
			return m_registry.get<Component>(castToRegistryIdentifier(entity));
		}
		template<typename... Component>
		void removeComponent(const Entity& entity)
		{
			m_registry.remove<Component...>(castToRegistryIdentifier(entity));
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

		Entity& getEntity(uint32_t id)
		{
			auto it = std::find_if(m_entities.begin(), m_entities.end(), [&](const Entity& _) -> bool { return _.getId() == id; });
			if (it == m_entities.end()) HLX_CORE_CRITICAL("Entity with id {0} does not exist", id);

			return *it;
		}
		std::vector<Entity>& getEntities() { return m_entities; }

	private:
		globalIdentifier castToGlobalIdentifier(entt::entity entity) { return static_cast<globalIdentifier>(entity); }
		localIdentifier castToRegistryIdentifier(const Entity& entity) { return static_cast<localIdentifier>(entity.getId()); }

		entt::registry m_registry;
		std::vector<Entity> m_entities;
	};
}
