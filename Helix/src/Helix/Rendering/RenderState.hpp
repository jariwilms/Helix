#pragma once

#include "Helix/Rendering/Function/RenderFunction.hpp"
#include "Helix/Rendering/API/RenderStateAPI.hpp"

namespace hlx
{
	class RenderState
	{
	public:
		static void init();

		static void enable(RenderFunction renderFunction);
		static void disable(RenderFunction renderFunction);

		static void selectRasterizationMode(RasterizationFunction rasterizationFunction);

	private:
		static RenderStateAPI* s_renderStateAPI;
	};
}
