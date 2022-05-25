#include "Helix.hpp"

class Sandbox : public hlx::Application
{
public:
	Sandbox() = default;
	~Sandbox() = default;
};

hlx::Application* hlx::create_application()
{
	return new Sandbox();
}