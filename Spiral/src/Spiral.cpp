#include "main.hpp"

#include "Layer/EditorLayer.hpp"

class Spiral : public hlx::Application
{
public:
	Spiral();
};

Spiral::Spiral() 
{
	pushLayer(new EditorLayer{});
}

hlx::Application* hlx::createApplication()
{
	return new Spiral();
}
