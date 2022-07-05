#include "stdafx.hpp"
#include "OpenGLRenderState.hpp"

namespace hlx
{
	OpenGLRenderState::OpenGLRenderState()
	{
        glEnable(GL_CULL_FACE); //TODO: => enable(RenderFunction::Cull);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
	}

	void OpenGLRenderState::enable(RenderFunction renderFunction)
    {
        auto capability = getRenderCapability(renderFunction);
        if (capability != -1) glEnable(capability);
    }
    void OpenGLRenderState::disable(RenderFunction renderFunction)
    {
		auto capability = getRenderCapability(renderFunction);
        if (capability != -1) glDisable(capability);
    }

	void OpenGLRenderState::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
        auto mode = getRasterizationMode(rasterizationFunction);
        if (mode != -1) glPolygonMode(GL_FRONT_AND_BACK, mode);
	}
}
