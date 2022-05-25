//#pragma once
//
//#include "stdafx.hpp"
//
//#include "GLAD/glad.h"
//#include "GLFW/glfw3.h"
//#include "GLM/glm.hpp"
//
//namespace hlx
//{
//	class InputHandler
//	{
//	public:
//		explicit InputHandler(GLFWwindow* window);
//
//		const std::vector<bool>& active_keys() const;
//		const std::vector<bool>& active_buttons() const;
//		const glm::vec2& cursor_position() const;
//		const glm::vec2& scroll_direction() const;
//
//		bool is_any_key_pressed() const;
//		bool is_key_pressed(int key) const;
//		bool is_key_pressed_once(int key) const;
//
//		bool is_any_button_pressed() const;
//		bool is_button_pressed(int button) const;
//		bool is_button_pressed_once(int button) const;
//
//		bool is_moving_cursor() const;
//		bool is_moving_cursor_x() const;
//		bool is_moving_cursor_y() const;
//
//		bool is_scrolling() const;
//		bool is_scrolling_x(int direction) const;
//		bool is_scrolling_y(int direction) const;
//
//		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//		void cursor_callback(GLFWwindow* window, double xpos, double ypos);
//		void button_callback(GLFWwindow* window, int button, int action, int mods);
//		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//		void update();
//
//	private:
//		GLFWwindow* m_window;
//
//		std::vector<bool> m_activeKeys;
//		std::vector<bool> m_lastActiveKeys;
//
//		std::vector<bool> m_activeButtons;
//		std::vector<bool> m_lastActiveButtons;
//
//		glm::vec2 m_cursorPosition;
//		glm::vec2 m_lastCursorPosition;
//
//		glm::vec2 m_scrollDirection;
//		glm::vec2 m_lastScrollDirection;
//
//		size_t m_activeKeyCount;
//		size_t m_activeButtonCount;
//
//		const unsigned int GLFW_KEY_COUNT = 348;
//		const unsigned int GLFW_BUTTON_COUNT = 8;
//	};
//}
