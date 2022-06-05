#pragma once

#include "stdafx.hpp"

#include "entt/entt.hpp"

#include "EntityRegistry.hpp"

#include "Camera/Camera.hpp"
#include "Components/Base/Component.hpp"
#include "Helix/Rendering/Objects/VertexArray.hpp"
#include "Helix/Rendering/Objects/VertexBuffer.hpp"
#include "Helix/Rendering/Objects/ElementBuffer.hpp"
#include "Helix/Rendering/Shader.hpp"
#include "Helix/Rendering/Texture.hpp"

namespace hlx
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void update();
		void render();

		EntityRegistry& getRegistry() const;

		const std::unordered_set<std::shared_ptr<Entity>>& getEntities() const;

		template <typename T>
		Entity& createEntity()
		{
			auto* entity = new T{ id };
			m_entities.emplace(entity);

			return *entity;
		}

		void destroyEntity(const Entity& entity);

	private:
		std::unique_ptr<EntityRegistry> m_registry;
		std::unordered_set<std::shared_ptr<Entity>> m_entities;

		hlx::Camera m_camera;

		std::shared_ptr<hlx::VertexArray> m_vao;
		std::shared_ptr<hlx::VertexBuffer> m_vbo;
		std::shared_ptr<hlx::ElementBuffer> m_ebo;

		std::shared_ptr<hlx::Shader> m_shader;
		std::shared_ptr<hlx::Texture> m_texture;
	};
}
