#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Helix/Library/DeltaTime.hpp"

namespace hlx
{
	class Widget
	{
	public:
		virtual ~Widget() = default;

		virtual void update(DeltaTime deltaTime) {}
		virtual void render() {}
		virtual void renderUI() {}

		inline bool isEnabled() const { return m_isEnabled; }
		inline bool isFocused() const { return m_isFocused; }

		inline void setEnabled(bool state) { m_isEnabled = state; }
		inline void setFocused(bool state) { m_isFocused = state; }

	protected:
		Widget() : m_isEnabled{ true }, m_isFocused{} {}

	private:
		bool m_isEnabled;
		bool m_isFocused;
	};
}
