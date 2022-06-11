#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/ECS/Component/ComponentArray.hpp"

namespace hlx
{
	//using Component = uint32_t;
	//using Identifier = size_t;

	//class Registry
	//{
	//public:
	//	Registry()
	//		: m_entityCount{}, m_newComponentId {}
	//	{
	//		for (int i = 0; i < 256; ++i)
	//			m_availableEntities.push(i);
	//	}

	//	Entity createEntity()
	//	{
	//		if (m_availableEntities.empty())
	//		{
	//			HLX_CORE_ERROR("Failed to create entity: out of valid identifiers");
	//			return -1;
	//		}

	//		auto id = m_availableEntities.front();
	//		m_availableEntities.pop();
	//		++m_entityCount;

	//		return id;
	//	}

	//	void destroyEntity(Entity entity)
	//	{
	//		m_availableEntities.push(entity);
	//		--m_entityCount;
	//	}

	//	template <typename Component>
	//	Component& addComponent(Entity entity)
	//	{
	//		auto& info = typeid(Component);
	//		auto hash = info.hash_code();

	//		if (m_componentIdentifiers.find(hash) == m_componentIdentifiers.end())
	//			registerComponent<Component>(hash);

	//		return getComponentArray<Component>()->addComponent(entity);
	//	}

	//	template <typename Component>
	//	bool hasComponent(Entity entity)
	//	{
	//		return getComponentArray<Component>()->hasComponent(entity);
	//	}

	//	template <typename Component>
	//	Component& getComponent(Entity entity)
	//	{
	//		return getComponentArray<Component>()->getComponent(entity);
	//	}

	//	template <typename Component>
	//	void removeComponent(Entity entity)
	//	{
	//		getComponentArray<Component>()->removeComponent(entity);
	//	}

	//private:
	//	template <typename Component>
	//	void registerComponent(size_t hash)
	//	{
	//		m_componentIdentifiers.insert(std::make_pair(hash, m_newComponentId));
	//		m_componentArrays.insert(std::make_pair(hash, std::make_shared<ComponentArray<Component>>()));

	//		++m_newComponentId;
	//	}

	//	template <typename Component>
	//	const std::shared_ptr<ComponentArray<Component>> getComponentArray()
	//	{
	//		assertExistence<Component>();

	//		auto& info = typeid(Component);
	//		auto hash = info.hash_code();

	//		HLX_CORE_ASSERT(m_componentArrays.find(hash) != m_componentArrays.end(), "Component array does not exist");

	//		return std::static_pointer_cast<ComponentArray<Component>>(m_componentArrays[hash]);
	//	}

	//	template <typename Component>
	//	void assertExistence()
	//	{
	//		auto& info = typeid(Component);
	//		auto hash = info.hash_code();

	//		HLX_CORE_ASSERT(m_componentIdentifiers.find(hash) != m_componentIdentifiers.end(), "Component does not exist");
	//	}

	//	std::queue<Entity> m_availableEntities;
	//	size_t m_entityCount;

	//	std::unordered_map<Identifier, std::shared_ptr<IComponentVector>> m_componentArrays; //Pointer to component array
	//	std::unordered_map<Identifier, Component> m_componentIdentifiers; //Identifier per component
	//	uint32_t m_newComponentId;
	//};
}
