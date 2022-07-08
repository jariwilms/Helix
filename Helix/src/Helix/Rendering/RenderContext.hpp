#pragma once

#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class RenderContext
	{
	public:
		static void create(WindowProperties& properties);
		
		static void enable(RenderFunction renderFunction);
		static void disable(RenderFunction renderFunction);

		static NativeWindow* getNativeWindow();
		
		static void setViewport(glm::uvec4 rectangle);
		static void setRasterizationMode(RasterizationFunction rasterizationFunction);
		static void setVSync(bool state);

		static void swapBuffers();
		static void pollEvents();

	private:
		static inline RenderContextAPI* s_renderStateAPI;
	};
}
