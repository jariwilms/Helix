#pragma once

#include "Helix/Core/DeltaTime.hpp"
#include "Helix/Core/Transform.hpp" //todo: move
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Rendering/Texture.hpp"

namespace hlx
{
	struct TransformComponent
	{
	public:
		TransformComponent(glm::vec3 position = glm::vec3{}, glm::vec3 rotation = glm::vec3{}, glm::vec3 scale = glm::vec3{ 1.0f })
			: transform{ position, rotation, scale } {}
		TransformComponent(Transform transform)
			: transform{ transform } {}

		operator glm::mat4() { return transform; }

		Transform transform;
	};

	struct SpriteComponent
	{
	public:
		SpriteComponent() = default;
		SpriteComponent(std::filesystem::path path)
			: texture{ Texture::create(path) } {}

		std::shared_ptr<Texture> texture;
	};
}
