#pragma once

#include <Helix.hpp>
#include <memory>

class TestLayer : public hlx::Layer
{
public:
	TestLayer()
	{
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

		m_vao = std::make_shared<hlx::VertexArray>();
		m_vbo = std::make_shared<hlx::VertexBuffer>(triangleVertices, (GLsizei)sizeof(triangleVertices));
		m_ebo = std::make_shared<hlx::ElementBuffer>(triangleIndices, (GLsizei)sizeof(triangleIndices));

		m_vbo->setLayout(layout);
		m_vao->setElementBuffer(*m_ebo);
		m_vao->addVertexBuffer(*m_vbo);
		
		m_shader = std::make_shared<hlx::Shader>("tex.vert", "tex.frag");
		HLX_CORE_ASSERT(m_shader->verify(), "Failed to create shader"); //TODO: move in shader?

		m_texture = std::make_shared<hlx::Texture>("kiryu.png");

		auto transform = hlx::Transform{};
		transform.translate({ 0.0f, 0.0f, 3.0f });
		m_camera = hlx::Camera{ transform, glm::vec3{0.0f, 1.0f, 0.0f}, hlx::Projection::Type::Orthographic };
	}

	void update() override
	{
		m_camera.update();

		m_shader->bind();
		m_shader->setMat("u_model", glm::mat4{ 1.0f });
		m_shader->setMat("u_view", m_camera.getViewMatrix());
		m_shader->setMat("u_projection", m_camera.getProjectionMatrix());
	}

	void render() override
	{
		auto& renderer = hlx::Renderer::getInstance();

		m_vao->bind();
		m_texture->bind();
		renderer.drawIndexed(*m_vao);
	}

private:
	hlx::Camera m_camera;

	std::shared_ptr<hlx::VertexArray> m_vao;
	std::shared_ptr<hlx::VertexBuffer> m_vbo;
	std::shared_ptr<hlx::ElementBuffer> m_ebo;

	std::shared_ptr<hlx::Shader> m_shader;
	std::shared_ptr<hlx::Texture> m_texture;
};