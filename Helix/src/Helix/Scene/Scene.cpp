#include "stdafx.hpp"
#include "Scene.hpp"

namespace hlx
{
	Scene::Scene()
	{
		m_camera = Camera{ Transform{ glm::vec3{ 0.0f, 0.0f, 3.0f } } };
		m_camera.setProjectionType(Projection::Type::Perspective);

		auto& spr1 = addComponent<SpriteComponent>(createEntity(), "textures/kiryu.png");
		spr1.transform.position.x += 0.5f;
		auto& spr2 = addComponent<SpriteComponent>(createEntity(), "textures/missing.png");
		spr2.transform.position.x -= 0.5f;
	}

	void Scene::update(DeltaTime deltaTime)
	{
		m_camera.update(deltaTime);

		Renderer::start(getCamera());

		auto view = m_registry.view<SpriteComponent>();

		for (auto entity : view)
		{
			auto& sprite = view.get<SpriteComponent>(entity);
			sprite.update(deltaTime);
		}

		Renderer::finish();
	}

	void Scene::render()
	{

	}

	const Camera& Scene::getCamera() const
	{
		return m_camera;
	}
}
