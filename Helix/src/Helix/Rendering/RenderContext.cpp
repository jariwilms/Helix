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

	void RenderContext::setViewport(glm::uvec4 rectangle)
	{
		s_renderStateAPI->setViewport(rectangle);
	}
	void RenderContext::setRasterizationMode(RasterizationFunction rasterizationFunction)
	{
		s_renderStateAPI->setRasterizationMode(rasterizationFunction);
	}
	void RenderContext::setVSync(bool state)
	{
		s_renderStateAPI->setVSync(state);
	}

	void RenderContext::swapBuffers(NativeWindow* window)
	{
		s_renderStateAPI->swapBuffers(window);
	}
	void RenderContext::pollEvents()
	{
		s_renderStateAPI->pollEvents();
	}

	void* RenderContext::createWindow(WindowProperties& properties)
	{
		return s_renderStateAPI->createWindow(properties);
	}
	void RenderContext::destroyWindow(NativeWindow* window)
	{
		s_renderStateAPI->destroyWindow(window);
	}
}
