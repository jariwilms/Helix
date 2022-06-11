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
		TransformComponent() = default;
		TransformComponent(Transform transform)
			: transform{ transform } {}

		Transform transform;
	};

	struct SpriteComponent
	{
	public:
		SpriteComponent(std::filesystem::path path)
		{
			texture = Texture::create(path);
			transform.scale = glm::vec3{ 1.0f };
		}

		void update(DeltaTime deltaTime)
		{
			Renderer::renderQuad(transform, texture);
		}

		std::shared_ptr<Texture> texture;
		Transform transform;
	};
}
