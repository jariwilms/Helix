#pragma once

//#include "GLFW/glfw3.h"

namespace hlx
{
	class WindowSettings
	{
	public:
		WindowSettings();
		WindowSettings(const char* title, unsigned int width, unsigned int height);

		const char* title;
		unsigned int width;
		unsigned int height;
	};

	class Window
	{
	public:
		Window() {}
		//virtual ~Window() = 0;

		virtual void update() = 0;

		virtual unsigned int width() const = 0;
		virtual unsigned int height() const = 0;

		virtual void set_vsync(bool state) = 0;

	protected:
		WindowSettings settings;
	};
}
