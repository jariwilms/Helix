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
		virtual ~Widget() = default;

		virtual void update(DeltaTime deltaTime) {}
		virtual void render() {}
		virtual void renderUI() {}

		inline bool isFocused() const { return m_isFocused; }

		inline void setFocused(bool state) { m_isFocused = state; }

	protected:
		Widget() : m_isFocused{} {}

	private:
		bool m_isFocused;
	};
}
