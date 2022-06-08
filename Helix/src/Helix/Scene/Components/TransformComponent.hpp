#pragma once

#include "Helix/Core/Transform.hpp"
#include "Helix/Scene/Entities/Base/Entity.hpp"
#include "Helix/Scene/Components/Base/Component.hpp"

namespace hlx
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(Entity* parent)
			: Component{ parent } {}

		COMPONENT_NAME("TransformComponent")
		COMPONENT_DEBUG("")

	private:
		Transform m_transform;
	};
}
