#pragma once

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>

namespace Core {
	struct WindowData {
	public:
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	struct NativeWindowHandle {
		enum class Type {
			Win32 = 0,
			GLFW
		};

		Type type;
		void* handle;
	};

	class IWindow {
	public:
		virtual ~IWindow() {}

		virtual void ClearScreen(const glm::vec4& clear_color) const = 0;
		virtual void OnUpdate() = 0;

		virtual const WindowData& GetWindowData() const = 0;
		virtual const NativeWindowHandle& GetWindowHandle() const = 0;
		virtual const bool& Running() const = 0;

		static IWindow* CreateWindow(const WindowData& window_data);
	};
}