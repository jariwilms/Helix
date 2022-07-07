#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/API/RenderContextAPI.hpp"

namespace hlx
{
	class OpenGLRenderContext : public RenderContextAPI
	{
	public:
		OpenGLRenderContext();

		void enable(RenderFunction renderFunction) override;
		void disable(RenderFunction renderFunction) override;

		void setRasterizationMode(RasterizationFunction rasterizationFunction) override;

	private:
		static constexpr int getRenderCapability(RenderFunction renderFunction)
		{
			switch (renderFunction)
			{
				case DepthTest:			return GL_DEPTH_TEST;
				case StencilTest:		return GL_STENCIL_TEST;
				case ScissorTest:		return GL_SCISSOR_TEST;
				default: HLX_CORE_ERROR("Invalid render function: {0}", static_cast<int>(renderFunction)); return -1;
			}
		}

		static constexpr int getRasterizationMode(RasterizationFunction rasterizationFunction)
		{
			switch (rasterizationFunction)
			{
				case Point:				return GL_POINT;
				case Line:				return GL_LINE;
				case Fill:				return GL_FILL;
				default: HLX_CORE_ERROR("Invalid rasterization function: {0}", static_cast<int>(rasterizationFunction)); return -1;
			}
		}
	};
}
