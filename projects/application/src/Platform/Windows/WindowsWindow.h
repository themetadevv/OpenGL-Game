#pragma once

#include "Core/Window.h"

namespace Platform::Windows {
	class Window : public Core::IWindow {
	private:
		Core::WindowData m_WindowData;
		Core::NativeWindowHandle m_NativeWindowHandle;
		GLFWwindow* m_Window;
		bool m_WindowRunning;

		void Initialize();

	public:
		Window(const Core::WindowData& window_data);

		void OnUpdate() override;
		void OnShutdown() override;

		const Core::WindowData& GetWindowData() const override {
			return m_WindowData;
		}

		const Core::NativeWindowHandle& GetWindowHandle() const override {
			return m_NativeWindowHandle;
		}

		const bool& Running() const override {
			return m_WindowRunning;
		}
	};
}