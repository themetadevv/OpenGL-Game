#pragma once

#include "Core/Window.h"

namespace Platform::Windows {
	class Window : public Core::IWindow {
	private:
		Core::WindowData m_WindowData;
		GLFWwindow* m_Window;
		bool m_WindowRunning;

		void Initialize();

	public:
		Window(const Core::WindowData& window_data);

		void ClearScreen(const glm::vec4& clear_color) const override;
		void OnUpdate() override;

		const Core::WindowData& GetWindowData() const override {
			return m_WindowData;
		}

		const Core::NativeWindowHandle& GetWindowHandle() const override {
			return Core::NativeWindowHandle(Core::NativeWindowHandle::Type::GLFW, m_Window);
		}

		const bool& Running() const override {
			return m_WindowRunning;
		}
	};
}