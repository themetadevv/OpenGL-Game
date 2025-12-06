
#include "pch.h"
#include "Core/Core.h"
#include "Core/Window.h"

#include "Input.h"

namespace Core {
	GLFWwindow* Input::m_sWindowHandle = nullptr;

	std::unordered_map<KeyCode, InputAction> Input::m_sKeyState;
	std::unordered_map<KeyCode, InputAction> Input::m_sLastKeyState;

	std::unordered_map<MouseCode, InputAction> Input::m_sMouseButtonState;
	std::unordered_map<MouseCode, InputAction> Input::m_sLastMouseButtonState;

	double Input::m_sMouseX = 0.0, Input::m_sMouseY = 0.0;
	double Input::m_sLastMouseX = 0.0, Input::m_sLastMouseY = 0.0;
	double Input::m_sMouseDeltaX = 0.0, Input::m_sMouseDeltaY = 0.0;
}