#pragma once

#include "Helix/Scene/Components/Base/Component.hpp"

namespace hlx
{
	class TestComponent : public Component
	{
	public:
		TestComponent(Entity* parent)
			: Component(parent), x{} {}

		COMPONENT_NAME("TestComponent")
		COMPONENT_DEBUG("TestComponent Debug")

	private:
		int x;
	};
}
