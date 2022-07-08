#pragma once

#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class RenderContext
	{
	public:
		static void init();
		
		static void enable(RenderFunction renderFunction);
		static void disable(RenderFunction renderFunction);

		static void setViewport(glm::uvec4 rectangle);
		static void setRasterizationMode(RasterizationFunction rasterizationFunction);
		static void setVSync(bool state);

		static void swapBuffers(NativeWindow* window);
		static void pollEvents();

		static void* createWindow(WindowProperties& properties);
		static void destroyWindow(NativeWindow* window);

	private:
		static inline RenderContextAPI* s_renderStateAPI;
	};
}
