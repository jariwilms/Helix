#pragma once

#include "Base/Component.hpp"
#include "Helix/Core/Transform.hpp"

namespace hlx
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent() = default;

		void update() override
		{
			std::cout << "tc\n";
		}

		COMPONENT_NAME("ASD")
		COMPONENT_DEBUG("DEF")
	};
}
