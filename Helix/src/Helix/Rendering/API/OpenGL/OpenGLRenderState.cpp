#include "stdafx.hpp"
#include "OpenGLRenderState.hpp"

namespace hlx
{
    void OpenGLRenderState::enable(RenderFunction renderFunction)
    {
        auto capability = getRenderCapability(renderFunction);
        glEnable(capability);
    }
    void OpenGLRenderState::disable(RenderFunction renderFunction)
    {
		auto capability = getRenderCapability(renderFunction);
        glDisable(capability);
    }

	void OpenGLRenderState::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
        auto mode = getRasterizationMode(rasterizationFunction);
        glPolygonMode(GL_FRONT_AND_BACK, mode);
	}

}
