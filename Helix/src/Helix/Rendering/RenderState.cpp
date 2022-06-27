#include "stdafx.hpp"
#include "RenderState.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGLRenderState.hpp"

namespace hlx
{
	void RenderState::init()
	{
		s_renderStateAPI = new OpenGLRenderState{};
	}

	void RenderState::enable(RenderFunction renderFunction)
	{
		s_renderStateAPI->enable(renderFunction);
	}

	void RenderState::disable(RenderFunction renderFunction)
	{
		s_renderStateAPI->disable(renderFunction);
	}

	void RenderState::selectRasterizationMode(RasterizationFunction rasterizationFunction)
	{
		s_renderStateAPI->selectRasterizationMode(rasterizationFunction);
	}

	RenderStateAPI* RenderState::s_renderStateAPI;
}
