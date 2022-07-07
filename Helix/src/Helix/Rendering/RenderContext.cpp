#include "stdafx.hpp"
#include "RenderContext.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGLRenderContext.hpp"

namespace hlx
{
	void RenderContext::init()
	{
		s_renderStateAPI = new OpenGLRenderContext{};
	}

	void RenderContext::enable(RenderFunction renderFunction)
	{
		s_renderStateAPI->enable(renderFunction);
	}

	void RenderContext::disable(RenderFunction renderFunction)
	{
		s_renderStateAPI->disable(renderFunction);
	}

	void RenderContext::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
		s_renderStateAPI->setRasterizationMode(rasterizationFunction);
	}
}
