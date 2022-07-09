#include "stdafx.hpp"
#include "Input.hpp"

#include "Helix/Core/Application.hpp"
#include "Helix/Rendering/RenderContext.hpp"

namespace hlx
{
	void Input::init()
	{
		m_window = (GLFWwindow*)RenderContext::getNativeWindow(); //verander naar base class window ptr

		m_activeKeys.resize(GLFW_KEY_COUNT);
		m_lastActiveKeys.resize(GLFW_KEY_COUNT);

		m_activeButtons.resize(GLFW_BUTTON_COUNT);
		m_lastActiveButtons.resize(GLFW_BUTTON_COUNT);

		HLX_CORE_INFO("Input initialized");
	}
	void Input::reset()
	{
		m_lastActiveKeys = m_activeKeys;
		m_lastActiveButtons = m_activeButtons;

		m_relativeCursorPosition = glm::vec2{ 0.0f };

		m_lastScrollDirection = m_scrollDirection;
		m_scrollDirection = glm::vec2{ 0.0f };
	}

	const std::vector<bool>& Input::getActiveKeys()
	{
		return m_lastActiveKeys;
	}
	const std::vector<bool>& Input::getActiveButtons()
	{
		return m_activeButtons;
	}
	const glm::vec2& Input::getCursorPosition()
	{
		return m_cursorPosition;
	}
	const glm::vec2& Input::getRelativeCursorPosition()
	{
		return m_relativeCursorPosition;
	}
	const glm::vec2& Input::getScrollDirection()
	{
		return m_scrollDirection;
	}

	bool Input::isAnyKeyPressed()
	{
		return m_activeKeyCount > 0;
	}
	bool Input::isKeyPressed(KeyCode keyCode)
	{
		return m_activeKeys[keyCode];
	}
	bool Input::isKeyPressedOnce(KeyCode keyCode)
	{
		return m_activeKeys[keyCode] && !m_lastActiveKeys[keyCode];
	}

	bool Input::isAnyButtonPressed()
	{
		return m_activeButtonCount > 0;
	}
	bool Input::isButtonPressed(MouseCode mouseCode)
	{
		return m_activeButtons[mouseCode];
	}
	bool Input::isButtonPressedOnce(MouseCode mouseCode)
	{
		return m_activeButtons[mouseCode] && !m_lastActiveButtons[mouseCode];
	}

	bool Input::isMovingCursor()
	{
		return m_cursorPosition != m_lastCursorPosition;
	}
	bool Input::isMovingCursorX()
	{
		return (m_cursorPosition - m_lastCursorPosition).x > 0;
	}
	bool Input::isMovingCursorY()
	{
		return (m_cursorPosition - m_lastCursorPosition).y > 0;
	}

	bool Input::isScrolling()
	{
		return m_scrollDirection.x != 0 || m_scrollDirection.y != 0;
	}
	bool Input::isScrollingX(int direction)
	{
		return m_scrollDirection.x == direction;
	}
	bool Input::isScrollingY(int direction)
	{
		return m_scrollDirection.y == direction;
	}

	void Input::setMouseLock(bool state)
	{
		auto mode = state ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
		glfwSetInputMode(m_window, GLFW_CURSOR, mode);
	}

	void Input::_inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key < Key::MIN_VALUE || key > Key::MAX_VALUE)
			return;

		if (action == GLFW_PRESS)
		{
			m_activeKeys.at(key) = true;
			++m_activeKeyCount;
		}
		if (action == GLFW_RELEASE)
		{
			m_activeKeys.at(key) = false;
			--m_activeKeyCount;
		}
	}
	void Input::_inputButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button < Button::MIN_VALUE || button > Button::MAX_VALUE)
			return;

		if (action == GLFW_PRESS)
		{
			m_activeButtons.at(button) = true;
			++m_activeButtonCount;
		}
		if (action == GLFW_RELEASE)
		{
			m_activeButtons.at(button) = false;
			--m_activeButtonCount;
		}
	}
	void Input::_inputCursorCallback(GLFWwindow* window, double x, double y)
	{
		m_lastCursorPosition = m_cursorPosition;
		m_cursorPosition = glm::vec2(x, y);

		m_relativeCursorPosition = m_cursorPosition - m_lastCursorPosition;
	}
	void Input::_inputScrollCallback(GLFWwindow* window, double x, double y)
	{
		m_lastScrollDirection = m_scrollDirection;
		m_scrollDirection = glm::vec2(x, y);
	}



	GLFWwindow* Input::m_window;

	std::vector<bool> Input::m_activeKeys;
	std::vector<bool> Input::m_lastActiveKeys;

	std::vector<bool> Input::m_activeButtons;
	std::vector<bool> Input::m_lastActiveButtons;

	glm::vec2 Input::m_cursorPosition;
	glm::vec2 Input::m_lastCursorPosition;
	glm::vec2 Input::m_relativeCursorPosition;

	glm::vec2 Input::m_scrollDirection;
	glm::vec2 Input::m_lastScrollDirection;

	size_t Input::m_activeKeyCount;
	size_t Input::m_activeButtonCount;
}
