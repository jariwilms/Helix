#pragma once

#include "stdafx.hpp"

#include "Fox/Input/Handler/InputHandlerAPI.hpp"

namespace fox
{
	using NativeWindow = void;

	class Window
	{
	public:
		enum class Mode
		{
			Windowed,
			Borderless,
			Fullscreen
		};

		virtual ~Window() = default;

		virtual void refresh() = 0;

		virtual void rename(const std::string& title) = 0;
		virtual void resize(const Vector2f& dimensions) = 0;

        NativeWindow* const native_handle() const
        {
            return m_nativeWindow;
        }

	protected:
		Window(const std::string& title, const Vector2u& dimensions)
            : m_title{ title }, m_dimensions{ dimensions } {}

        std::string m_title{};
        Vector2f    m_dimensions{};
        Mode        m_displayMode{};

		NativeWindow* m_nativeWindow{};
	};
}
