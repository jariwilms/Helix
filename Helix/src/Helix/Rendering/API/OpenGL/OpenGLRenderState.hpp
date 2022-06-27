#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/API/RenderStateAPI.hpp"

namespace hlx
{
	class OpenGLRenderState : public RenderStateAPI
	{
	public:
		void enable(RenderFunction renderFunction) override;
		void disable(RenderFunction renderFunction) override;

		void selectRasterizationMode(RasterizationFunction rasterizationFunction) override;

	private:
		static constexpr int getRenderCapability(RenderFunction renderFunction)
		{
			switch (renderFunction)
			{
				case DepthTest:			return GL_DEPTH_TEST;
				case StencilTest:		return GL_STENCIL_TEST;
				case ScissorTest:		return GL_SCISSOR_TEST;
				default: HLX_CORE_CRITICAL("Invalid render function: {0}", static_cast<int>(renderFunction));
			}
		}

		static constexpr int getRasterizationMode(RasterizationFunction rasterizationFunction)
		{
			switch (rasterizationFunction)
			{
				case Point:				return GL_POINT;
				case Line:				return GL_LINE;
				case Fill:				return GL_FILL;
				default: HLX_CORE_CRITICAL("Invalid rasterization function: {0}", static_cast<int>(rasterizationFunction));
			}
		}
	};
}
