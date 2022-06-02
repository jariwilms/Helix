#include <Helix.hpp>

class Sandbox : public hlx::Application
{
public:
	Sandbox(const std::string& name);
	~Sandbox() = default;
};

hlx::Application* hlx::createApplication()
{
	return new Sandbox("");
}

Sandbox::Sandbox(const std::string& name)
	: Application(name)
{

}
