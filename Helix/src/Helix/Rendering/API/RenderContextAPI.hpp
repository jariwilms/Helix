#pragma once

#include "Helix/Rendering/Function/RasterizationFunction.hpp"
#include "Helix/Rendering/Function/RenderFunction.hpp"

namespace hlx
{
	class RenderContextAPI
	{
	public:
		virtual ~RenderContextAPI() = default;

		virtual void enable(RenderFunction renderFunction) = 0;
		virtual void disable(RenderFunction renderFunction) = 0;

		virtual void setRasterizationMode(RasterizationFunction rasterizationFunction) = 0;
	};
}
