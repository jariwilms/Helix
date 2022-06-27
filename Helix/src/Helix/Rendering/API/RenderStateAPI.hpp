#pragma once

#include "Helix/Rendering/Function/RasterizationFunction.hpp"
#include "Helix/Rendering/Function/RenderFunction.hpp"

namespace hlx
{
	class RenderStateAPI
	{
	public:
		virtual ~RenderStateAPI() = default;

		virtual void enable(RenderFunction renderFunction) = 0;
		virtual void disable(RenderFunction renderFunction) = 0;

		virtual void selectRasterizationMode(RasterizationFunction rasterizationFunction) = 0;
	};
}
