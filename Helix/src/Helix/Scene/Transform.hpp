#pragma once

#include "glm/glm.hpp"

namespace hlx
{
	struct Transform
	{
		Transform()
			: position{}, rotation{}, scale{} {}

		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
			: position{ position }, rotation{ rotation }, scale{ scale } {}

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}
