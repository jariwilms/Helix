#pragma once

#include "stdafx.hpp"

#include "Helix/Input/Input.hpp"
#include "Helix/Rendering/Function/RasterizationFunction.hpp"
#include "Helix/Rendering/Function/RenderFunction.hpp"
#include "Helix/Window/Window.hpp"

namespace hlx
{
	class RenderContextAPI
	{
	public:
		virtual ~RenderContextAPI() = default;

		virtual void enable(RenderFunction renderFunction) = 0;
		virtual void disable(RenderFunction renderFunction) = 0;

		virtual void setViewport(glm::uvec4 rectangle) = 0;
		virtual void setRasterizationMode(RasterizationFunction rasterizationFunction) = 0;
		virtual void setVSync(bool state) = 0;

		virtual void swapBuffers(NativeWindow* window) = 0;
		virtual void pollEvents() = 0;

		virtual void* createWindow(WindowProperties& properties) = 0;
		virtual void destroyWindow(NativeWindow* window) = 0;

	protected:
		RenderContextAPI() = default;
	};
}
