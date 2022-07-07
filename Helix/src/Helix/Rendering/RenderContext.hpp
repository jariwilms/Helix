#pragma once

#include "Helix/Rendering/Function/RenderFunction.hpp"
#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class RenderContext
	{
	public:
		static void init();

		static void enable(RenderFunction renderFunction);
		static void disable(RenderFunction renderFunction);

		static void setRasterizationMode(RasterizationFunction rasterizationFunction);

	private:
		static inline RenderContextAPI* s_renderStateAPI;
	};
}
