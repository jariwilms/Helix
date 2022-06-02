#include "TestLayer.hpp"

TestLayer::TestLayer()
{
	hlx::Renderer& renderer = hlx::Renderer::getInstance();

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

	hlx::VertexArray vao{};
	hlx::VertexBuffer vbo{ triangleVertices, sizeof(triangleVertices) };
	hlx::ElementBuffer ebo{ triangleIndices, sizeof(triangleIndices) };

	vbo.setLayout(layout);
	vao.addVertexBuffer(vbo);
	vao.setElementBuffer(ebo);

	hlx::Shader shader{ "tex.vert", "tex.frag" };
	HLX_CORE_ASSERT(shader.verify(), "Failed to create shader"); //TODO: move in shader?


	hlx::Texture texture{ "kiryu.png" };
	texture.bind();



	hlx::Camera camera{};


}

TestLayer::~TestLayer()
{

}

void TestLayer::update()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void TestLayer::render()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void TestLayer::onAttach()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void TestLayer::onDetach()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void TestLayer::onEvent(hlx::Event& m_event)
{
	throw std::logic_error("The method or operation is not implemented.");
}
