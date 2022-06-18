#include "stdafx.hpp"
#include "main.hpp"

#include "Layer/EditorLayer.hpp"

class Spiral : public hlx::Application
{
public:
	Spiral();

private:
	hlx::IO::Affix m_root;
};

Spiral::Spiral() 
	: m_root{ "Spiral/assets" } 
{ 
	pushLayer(new EditorLayer{}); 
}

hlx::Application* hlx::createApplication() { return new Spiral(); }
