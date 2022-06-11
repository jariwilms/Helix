#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Entity/Entity.hpp"

namespace hlx
{
	//class IComponentVector
	//{
	//public:
	//	virtual ~IComponentVector() = default;
	//	virtual void onEntityDestroyed() = 0;
	//};

	//template <typename Component>
	//class ComponentArray : public IComponentVector
	//{
	//public:
	//	ComponentArray()
	//		: m_componentCount{} {}

	//	const std::vector<Component>& getComponents()
	//	{
	//		return m_components;
	//	}

	//	Component& addComponent(Entity entity)
	//	{
	//		if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
	//		{
	//			HLX_CORE_WARNING("Entity #{0} already contains component <{1}>", entity, typeid(Component).name());
	//			return m_components[m_entityToIndexMap[entity]];
	//		}

	//		auto index = m_componentCount;
	//		m_indexToEntityMap.insert(std::make_pair(index, entity));
	//		m_entityToIndexMap.insert(std::make_pair(entity, index));

	//		m_components.emplace(m_components.begin() + m_componentCount, std::move(Component{}));
	//		++m_componentCount;

	//		return m_components[m_componentCount - 1];
	//	}

	//	bool hasComponent(Entity entity)
	//	{
	//		return m_entityToIndexMap.find(entity) != m_entityToIndexMap.end();
	//	}

	//	Component& getComponent(Entity entity)
	//	{
	//		HLX_CORE_ASSERT(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(), "Failed to get component");

	//		return m_components[m_entityToIndexMap[entity]];
	//	}

	//	void removeComponent(Entity entity) //TODO: fix
	//	{
	//		HLX_CORE_ASSERT(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end(), "Failed to remove component");

	//		auto entityIndex = m_entityToIndexMap[entity];
	//		auto lastIndex = m_componentCount - 1;
	//		auto lastEntity = m_indexToEntityMap[lastIndex];

	//		m_components[entityIndex] = m_components[lastIndex];

	//		m_entityToIndexMap[lastEntity] = entityIndex;
	//		m_indexToEntityMap[entityIndex] = lastEntity;

	//		m_entityToIndexMap.erase(entity);
	//		m_indexToEntityMap.erase(lastIndex);

	//		--m_componentCount;
	//	}

	//	void onEntityDestroyed() override
	//	{

	//	}

	//private:
	//	std::vector<Component> m_components;
	//	size_t m_componentCount;

	//	std::unordered_map<size_t, Entity> m_indexToEntityMap;
	//	std::unordered_map<Entity, size_t> m_entityToIndexMap;
	//};
}
