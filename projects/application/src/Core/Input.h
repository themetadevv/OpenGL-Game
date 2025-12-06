#pragma once

#include "InputCodes.h"

namespace Core {
	enum class InputAction {
		None = -1,
		Press,
		Release,
	};

	class Input {
	private:
		static GLFWwindow* m_sWindowHandle;

		static std::unordered_map<KeyCode, InputAction> m_sKeyState;
		static std::unordered_map<KeyCode, InputAction> m_sLastKeyState;

		static std::unordered_map<MouseCode, InputAction> m_sMouseButtonState;
		static std::unordered_map<MouseCode, InputAction> m_sLastMouseButtonState;

		static double m_sMouseX, m_sMouseY;
		static double m_sLastMouseX, m_sLastMouseY;
		static double m_sMouseDeltaX, m_sMouseDeltaY;

	private:
		static int GetInputAction(InputAction action) {
			switch (action) {
				case InputAction::None: return 0; break;
				case InputAction::Press: return GLFW_PRESS; break;
				case InputAction::Release: return GLFW_RELEASE; break;
				default: return 0; break;
			}
		}

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GetInputAction(InputAction::Press)) {
				m_sKeyState[(KeyCode)key] = InputAction::Press;
				Log("Key[", GetKeyCodeString((KeyCode)key), "] Down!");
			}
			else if (action == GetInputAction(InputAction::Release)) {
				m_sKeyState[(KeyCode)key] = InputAction::Release;
				Log("Key[", GetKeyCodeString((KeyCode)key), "] Released!");
			}
		}

		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
			if (action == GetInputAction(InputAction::Press)) {
				m_sMouseButtonState[(MouseCode)button] = InputAction::Press;
				Log("MouseButton[", GetMouseCodeString((MouseCode)button), "] Released!");
			}
			else if (action == GetInputAction(InputAction::Release)) {
				m_sMouseButtonState[(MouseCode)button] = InputAction::Release;
				Log("MouseButton[", GetMouseCodeString((MouseCode)button), "] Released!");
			}
		}

		static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
			m_sMouseX = xpos;
			m_sMouseY = ypos;
		}

	public:
		static void Init(GLFWwindow* window_handle) {
			m_sWindowHandle = window_handle;
			CORE_ASSERT(m_sWindowHandle, "Window Handle is null\n");

			for (int key = 0; key <= GLFW_KEY_LAST; key++)
				m_sKeyState[(KeyCode)key] = InputAction::None;

			for (int button = 0; button <= GLFW_MOUSE_BUTTON_LAST; button++)
				m_sMouseButtonState[(MouseCode)button] = InputAction::None;
			
			glfwSetKeyCallback(m_sWindowHandle, KeyCallback);
			glfwSetMouseButtonCallback(m_sWindowHandle, MouseButtonCallback);
			glfwSetCursorPosCallback(m_sWindowHandle, MousePositionCallback);
		}

		static void Update() {
			m_sMouseDeltaX = m_sMouseX - m_sLastMouseX;
			m_sMouseDeltaY = m_sMouseY - m_sLastMouseY;
			m_sLastMouseX = m_sMouseX;
			m_sLastMouseY = m_sMouseY;

			for (auto& [key, action] : m_sKeyState)
				m_sLastKeyState[key] = action;

			for (auto& [button, action] : m_sMouseButtonState)
				m_sLastMouseButtonState[button] = action;
		}

		// ------------------------------- KEYBOARD -----------------------------------

		static bool IsKeyDown(KeyCode key) {
			return m_sKeyState[key] == InputAction::Press;
		}

		static bool IsKeyPressed(KeyCode key) {
			return m_sKeyState[key] == InputAction::Press && m_sLastKeyState[key] != InputAction::Press;
		}

		static bool IsKeyReleased(KeyCode key) {
			return m_sKeyState[key] == InputAction::Release;
		}

		// ------------------------------- MOUSE -----------------------------------

		static bool IsMouseButtonDown(MouseCode button) {
			return m_sMouseButtonState[button] == InputAction::Press;
		}

		static bool IsMouseButtonPressed(MouseCode button) {
			return m_sMouseButtonState[button] == InputAction::Press && m_sLastMouseButtonState[button] != InputAction::Press;
		}

		static bool IsMouseButtonReleased(MouseCode button) {
			return m_sMouseButtonState[button] == InputAction::Release;
		}

		// ------------------------------- MOUSE CURSOR INFO -----------------------------------

		inline static double GetMousePosX() {
			return m_sMouseX;
		}

		inline static double GetMousePosY() {
			return m_sMouseY;
		}

		inline static double GetMouseDeltaPosX() {
			return m_sMouseDeltaX;
		}

		inline static double GetMouseDeltaPosY() {
			return m_sMouseDeltaY;
		}
	};
}