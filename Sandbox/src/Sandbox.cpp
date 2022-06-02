#include "main.hpp"

#include "Layers/TestLayer.hpp"

class Sandbox : public hlx::Application
{
public:
	Sandbox();
};

Sandbox::Sandbox() 
{
	pushLayer(new TestLayer{});
}

hlx::Application* hlx::createApplication()
{
	return new Sandbox();
}
