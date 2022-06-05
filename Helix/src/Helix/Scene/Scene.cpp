#include "stdafx.hpp"
#include "Scene.hpp"
#include "Entities/Base/Entity.hpp"

namespace hlx
{
	Scene::Scene()
	{
		m_registry = std::make_unique<EntityRegistry>();

		float triangleVertices[] = {
			// positions // colors // texture coords
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
		};
		unsigned int triangleIndices[] =
		{
			0, 1, 2,
			0, 2, 3,
		};

		hlx::BufferLayout layout{};
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(3);
		layout.addAttribute<float>(2);

		m_vao = hlx::VertexArray::create();
		m_vbo = hlx::VertexBuffer::create(triangleVertices, sizeof(triangleVertices));
		m_ebo = hlx::ElementBuffer::create(triangleIndices, sizeof(triangleIndices));

		m_vbo->setLayout(layout);
		m_vao->setElementBuffer(m_ebo);
		m_vao->addVertexBuffer(m_vbo);

		m_shader = hlx::Shader::create("tex.vert", "tex.frag");
		m_texture = hlx::Texture::create("kiryu.png");

		hlx::Transform transform{ glm::vec3{0.0f, 0.0f, 3.0f} };
		m_camera = hlx::Camera{ transform, glm::vec3{0.0f, 1.0f, 0.0f}, hlx::Projection::Type::Perspective };
	}

	Scene::~Scene()
	{

	}

	void Scene::update()
	{
		m_camera.update();

		for (auto& entity : m_entities)
			entity->update();
	}

	void Scene::render()
	{
		m_shader->bind();
		m_shader->setMat("u_model", glm::mat4{ 1.0f });
		m_shader->setMat("u_view", m_camera.getViewMatrix());
		m_shader->setMat("u_projection", m_camera.getProjectionMatrix());

		m_vao->bind();
		m_texture->bind();
		hlx::Renderer::render(*m_vao);

		for (auto& entity : m_entities)
			entity->render();
	}

	EntityRegistry& Scene::getRegistry() const
	{
		return *m_registry;
	}

	const std::unordered_set<std::shared_ptr<Entity>>& Scene::getEntities() const
	{
		return m_entities;
	}

	void Scene::destroyEntity(const Entity& entity)
	{
		auto lambda = [&](std::shared_ptr<Entity> element) -> bool { return element.get() == &entity; };
		auto it = std::find_if(m_entities.begin(), m_entities.end(), lambda);
		if (it != m_entities.end()) m_entities.erase(it);
	}
}
