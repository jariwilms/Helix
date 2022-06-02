#include <Helix.hpp>

class Sandbox : public hlx::Application
{
public:
	Sandbox();
	~Sandbox() override;
};

Sandbox::Sandbox() 
{

}

Sandbox::~Sandbox()
{

}

hlx::Application* hlx::createApplication()
{
	return new Sandbox();
}
