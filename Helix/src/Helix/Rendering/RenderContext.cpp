#include "stdafx.hpp"
#include "RenderContext.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGLRenderContext.hpp"

namespace hlx
{
	void RenderContext::create(WindowProperties& properties)
	{
		s_renderStateAPI = new OpenGLRenderContext{properties};
	}

	void RenderContext::enable(RenderFunction renderFunction)
	{
		s_renderStateAPI->enable(renderFunction);
	}
	void RenderContext::disable(RenderFunction renderFunction)
	{
		s_renderStateAPI->disable(renderFunction);
	}

	NativeWindow* RenderContext::getNativeWindow()
	{
		return s_renderStateAPI->getNativeWindow();
	}

	void RenderContext::setViewport(glm::uvec4 rectangle)
	{
		s_renderStateAPI->setViewport(rectangle);
	}
	void RenderContext::setScissor(glm::uvec4 rectangle)
	{
		s_renderStateAPI->setScissor(rectangle);
	}
	void RenderContext::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
		s_renderStateAPI->setRasterizationMode(rasterizationFunction);
	}
	void RenderContext::setVSync(bool state)
	{
		s_renderStateAPI->setVSync(state);
	}

	void RenderContext::swapBuffers()
	{
		s_renderStateAPI->swapBuffers();
	}
	void RenderContext::pollEvents()
	{
		s_renderStateAPI->pollEvents();
	}
}
