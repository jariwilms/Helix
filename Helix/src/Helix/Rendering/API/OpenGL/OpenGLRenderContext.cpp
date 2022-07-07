#include "stdafx.hpp"
#include "OpenGLRenderContext.hpp"

namespace hlx
{
	OpenGLRenderContext::OpenGLRenderContext()
	{

	}

	void OpenGLRenderContext::enable(RenderFunction renderFunction)
    {
        auto capability = getRenderCapability(renderFunction);
        if (capability != -1) glEnable(capability);
    }
    void OpenGLRenderContext::disable(RenderFunction renderFunction)
    {
		auto capability = getRenderCapability(renderFunction);
        if (capability != -1) glDisable(capability);
    }

	void OpenGLRenderContext::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
        auto mode = getRasterizationMode(rasterizationFunction);
        if (mode != -1) glPolygonMode(GL_FRONT_AND_BACK, mode);
	}
}
