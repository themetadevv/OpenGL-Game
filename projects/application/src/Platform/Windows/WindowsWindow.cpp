
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "WindowsWindow.h"

namespace Platform::Windows {
	void Window::Initialize() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		int glfw_init_success = glfwInit();
		CORE_ASSERT(glfw_init_success, "Failed to Initialize GLFW!");

		m_Window = glfwCreateWindow(m_WindowData.Width, m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
		CORE_ASSERT(m_Window, "Window* is null!");
		
		glfwMakeContextCurrent(m_Window);

		glfwSwapInterval(m_WindowData.VSync);

		int load_gl_loader_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(load_gl_loader_success, "Failed to load 'glad GL Loader'!");

		m_NativeWindowHandle.type = Core::NativeWindowHandle::Type::GLFW;
		m_NativeWindowHandle.handle = static_cast<GLFWwindow*>(m_Window);
	}

	Window::Window(const Core::WindowData& window_data) :
		m_WindowData(window_data), m_Window(nullptr), m_WindowRunning(true)
	{
		Initialize();
	}

	void Window::OnUpdate() {
		m_WindowRunning = !glfwWindowShouldClose(m_Window);
	
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::OnShutdown() {
		glfwSetWindowShouldClose(m_Window, true);
	}

}
