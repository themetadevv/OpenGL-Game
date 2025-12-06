#pragma once

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

		virtual void OnUpdate() = 0;
		virtual void OnShutdown() = 0;

		virtual const WindowData& GetWindowData() const = 0;
		virtual const NativeWindowHandle& GetWindowHandle() const = 0;

		virtual const bool& Running() const = 0;

		static IWindow* CreateWindow(const WindowData& window_data);
	};
}