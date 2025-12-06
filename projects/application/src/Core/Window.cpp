
#include "pch.h"
#include "Core.h"

#include "Platform/Windows/WindowsWindow.h"

#include "Window.h"

namespace Core {
	IWindow* IWindow::CreateWindow(const WindowData& window_data) {
#ifdef PLATFORM_WINDOWS
		return new Platform::Windows::Window(window_data);
#endif
	}
}