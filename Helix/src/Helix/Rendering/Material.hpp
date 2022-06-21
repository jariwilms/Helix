#pragma once

#include "glm/glm.hpp"

namespace hlx
{
	struct Material2D
	{
	public:
		Material2D() = default;
		~Material2D() = default;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
