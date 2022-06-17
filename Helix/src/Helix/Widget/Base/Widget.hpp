#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Core/DeltaTime.hpp"

namespace hlx
{
	class Widget
	{
	public:
		virtual ~Widget() {}

		virtual void update(DeltaTime deltaTime) {}
		virtual void render() {}
		virtual void renderUI() {}

	protected:
		Widget() = default;
	};
}
