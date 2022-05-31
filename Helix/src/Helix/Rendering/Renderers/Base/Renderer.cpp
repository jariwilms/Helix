#include "stdafx.hpp"
#include "Renderer.hpp"

#include "Helix/Rendering/Renderers/OpenGlRenderer.hpp"

namespace hlx
{
	Renderer* Renderer::s_instance;

	void Renderer::init()
	{
		s_instance = new OpenGlRenderer();
	}

	Renderer& Renderer::getInstance()
	{
		return *s_instance;
	}
}
