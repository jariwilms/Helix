#pragma once

#include "stdafx.hpp"

#include "Helix/Library/DeltaTime.hpp"
#include "Helix/Library/Transform.hpp" //todo: move
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"

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
		SpriteComponent()
			: texture{ Texture::create("textures/white.png") } {}
		SpriteComponent(std::filesystem::path path)
			: texture{ Texture::create(path) } {}

		std::shared_ptr<Texture> texture;
	};

	struct ModelComponent
	{
	public:
		ModelComponent(std::filesystem::path path)
			: model{ IO::load<Model>(path) } {}

		std::shared_ptr<Model> model;
	};

	struct CameraComponent
	{
		CameraComponent() = default;

		float x;
	};
}
