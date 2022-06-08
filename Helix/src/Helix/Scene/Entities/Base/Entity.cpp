#include "stdafx.hpp"
#include "Entity.hpp"

#include "Helix/Scene/Components/TransformComponent.hpp"
#include "Helix/Scene/Components/SpriteComponent.hpp"

namespace hlx
{
	Entity::Entity(Scene* scene)
		: m_scene{ scene }
	{
		auto& registry = m_scene->getRegistry();
		m_id = registry.create();

		addComponent<TransformComponent>();
	}
	Entity::~Entity()
	{
		auto& registry = m_scene->getRegistry();
		registry.destroy(m_id);
	}

	void Entity::update()
	{
		for (auto& component : m_components)
			component->update();
	}
	void Entity::render()
	{
		for (auto& component : m_components)
			component->render();
	}
}
