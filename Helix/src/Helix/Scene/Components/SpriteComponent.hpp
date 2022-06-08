#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Rendering/Texture.hpp"
#include "Helix/Scene/Components/Base/Component.hpp"
#include "Helix/Scene/Components/TransformComponent.hpp"

namespace hlx
{
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(Entity* parent)
			: Component{ parent }
		{
			setTexture("images/missing.png");
		}
		SpriteComponent(Entity* parent, std::filesystem::path texture)
			: Component{ parent }
		{
			setTexture(texture);
		}

		void render() override
		{
			Renderer::renderQuad(glm::vec3{ 0.0f, 0.0f, 0.0f });
		}

		Texture& getTexture() const
		{
			return *m_sprite;
		}
		void setTexture(std::filesystem::path texture)
		{
			m_sprite = Texture::create(texture);
		}

		COMPONENT_NAME("SpriteComponent")
		COMPONENT_DEBUG("")

	private:
		std::shared_ptr<Texture> m_sprite;
		TransformComponent* m_parentTransform;
	};
}
