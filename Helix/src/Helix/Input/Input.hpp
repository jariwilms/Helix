#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Helix/Input/KeyCode.hpp"
#include "Helix/Input/MouseCode.hpp"

namespace hlx
{
	class Input
	{
	public:
		static void init();
		static void reset();

		static const std::vector<bool>& getActiveKeys();
		static const std::vector<bool>& getActiveButtons();
		static const glm::vec2& getCursorPosition();
		static const glm::vec2& getRelativeCursorPosition();
		static const glm::vec2& getScrollDirection();

		static bool isAnyKeyPressed();
		static bool isKeyPressed(KeyCode keyCode);
		static bool isKeyPressedOnce(KeyCode keyCode);

		static bool isAnyButtonPressed();
		static bool isButtonPressed(MouseCode mouseCode);
		static bool isButtonPressedOnce(MouseCode mouseCode);

		static bool isMovingCursor();
		static bool isMovingCursorX();
		static bool isMovingCursorY();

		static bool isScrolling();
		static bool isScrollingX(int direction);
		static bool isScrollingY(int direction);

		static void _inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void _inputButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void _inputCursorCallback(GLFWwindow* window, double x, double y);
		static void _inputScrollCallback(GLFWwindow* window, double x, double y);

	private:
		static std::vector<bool> m_activeKeys;
		static std::vector<bool> m_lastActiveKeys;

		static std::vector<bool> m_activeButtons;
		static std::vector<bool> m_lastActiveButtons;

		static glm::vec2 m_cursorPosition;
		static glm::vec2 m_lastCursorPosition;
		static glm::vec2 m_relativeCursorPosition;

		static glm::vec2 m_scrollDirection;
		static glm::vec2 m_lastScrollDirection;

		static size_t m_activeKeyCount;
		static size_t m_activeButtonCount;

		static const unsigned int GLFW_KEY_COUNT = 348;
		static const unsigned int GLFW_BUTTON_COUNT = 8;
	};
}
