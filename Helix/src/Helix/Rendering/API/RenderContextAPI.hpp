#pragma once

#include "stdafx.hpp"

#include "Helix/Input/Input.hpp"
#include "Helix/Rendering/Function/RasterizationFunction.hpp"
#include "Helix/Rendering/Function/RenderFunction.hpp"
#include "Helix/Window/Window.hpp"

namespace hlx
{
	using NativeWindow = void;

	class RenderContextAPI
	{
	public:
		virtual ~RenderContextAPI() = default;

		virtual void enable(RenderFunction renderFunction) = 0;
		virtual void disable(RenderFunction renderFunction) = 0;

		virtual NativeWindow* getNativeWindow() { return m_nativeWindow; }

		virtual void setViewport(glm::uvec4 rectangle) = 0;
		virtual void setRasterizationMode(RasterizationFunction rasterizationFunction) = 0;
		virtual void setVSync(bool state) = 0;

		virtual void swapBuffers() = 0;
		virtual void pollEvents() = 0;

	protected:
		RenderContextAPI()
		{
#ifdef _WIN32
			m_platform = "Windows";
#endif

#ifdef __linux__
			m_platform = "Linux";
#endif
			
#ifdef __APPLE__
			m_platform = "MacOS";
#endif
		}

		NativeWindow* m_nativeWindow;

		std::string m_platform;
		std::string m_vendor;
		std::string m_renderer;
		std::string m_version;
	};
}
