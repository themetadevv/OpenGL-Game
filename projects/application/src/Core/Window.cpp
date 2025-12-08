
#include "pch.h"
#include "Core.h"

#include "Window.h"

namespace Core {

	// <------------------ Constructors/Deconstructor ------------------>

	Window::Window(const WindowSpecification& window_specs) :
		m_WindowSpecs(window_specs), m_WindowHandle(nullptr), m_PrimaryMonitorHandle(nullptr), m_Running(true), m_Initialized(false)
	{
		m_CurrentVideoMode = window_specs.VidMode;
		m_CurrentWindowState = window_specs.WinState;
		m_WindowPosition.first = 0;
		m_WindowPosition.second = 0;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_FOCUSED, false);

		int glfw_init_status = glfwInit();
		CORE_ASSERT(glfw_init_status, "Failed to Initialize GLFW!");

		m_WindowHandle = glfwCreateWindow(
			m_WindowSpecs.Size.first, m_WindowSpecs.Size.second,
			m_WindowSpecs.Title.c_str(), nullptr, nullptr
		);

		glfwMakeContextCurrent(m_WindowHandle);
		glfwSwapInterval(m_WindowSpecs.VSync ? 1 : 0);

		glfwGetWindowPos(m_WindowHandle, &m_WindowPosition.first, &m_WindowPosition.second);
		glfwGetWindowSize(m_WindowHandle, &m_WindowSpecs.Size.first, &m_WindowSpecs.Size.second);

		m_PrimaryMonitorHandle = glfwGetPrimaryMonitor();
		CORE_ASSERT(m_PrimaryMonitorHandle, "PrimaryMonitorHandle* is null");

		if (m_CurrentVideoMode != VideoMode::Windowed)
			SetVideoMode(m_CurrentVideoMode);

		SetWindowState(m_CurrentWindowState);

		int load_gl_loader_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(load_gl_loader_success, "Failed to load 'glad GL Loader'!");

		m_Initialized = true;
	}

	Window::~Window() {
		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();
	}

	// <------------------ Setters ------------------>

	void Window::SetWindowVSync(bool val) {
		m_WindowSpecs.VSync = val;
	}

	void Window::SetWindowSize(int w, int h) {
		m_WindowSpecs.Size.first = w;
		m_WindowSpecs.Size.second = h;
	}

	void Window::SetVideoMode(VideoMode vm) {
		if (m_CurrentVideoMode == vm && m_Initialized)
			return;

		const GLFWvidmode* current_video_mode_data = glfwGetVideoMode(m_PrimaryMonitorHandle);

		switch (vm) {
			case Core::VideoMode::Windowed: {
				glfwSetWindowAttrib(m_WindowHandle, GLFW_DECORATED, true);
				glfwSetWindowAttrib(m_WindowHandle, GLFW_RESIZABLE, true);

				glfwSetWindowMonitor(
					m_WindowHandle, nullptr,
					m_WindowPosition.first, m_WindowPosition.second,
					m_WindowSpecs.Size.first, m_WindowSpecs.Size.second,
					NULL
				);

				m_CurrentVideoMode = vm;
				break;
			}

			case Core::VideoMode::Borderless: {
				glfwSetWindowAttrib(m_WindowHandle, GLFW_DECORATED, false);
				glfwSetWindowAttrib(m_WindowHandle, GLFW_RESIZABLE, false);

				if (m_CurrentVideoMode == VideoMode::Windowed) {
					glfwGetWindowSize(m_WindowHandle, &m_WindowSpecs.Size.first, &m_WindowSpecs.Size.second);
					glfwGetWindowPos(m_WindowHandle, &m_WindowPosition.first, &m_WindowPosition.second);
				}

				glfwSetWindowMonitor(
					m_WindowHandle, nullptr,
					0, 0,
					current_video_mode_data->width, current_video_mode_data->height, // monitor's (w,h)
					NULL
				);

				m_CurrentVideoMode = vm;
				break;
			}
			
			case Core::VideoMode::Fullscreen: {
				glfwSetWindowAttrib(m_WindowHandle, GLFW_DECORATED, false);
				glfwSetWindowAttrib(m_WindowHandle, GLFW_RESIZABLE, false);

				if (m_CurrentVideoMode == VideoMode::Windowed) {
					glfwGetWindowSize(m_WindowHandle, &m_WindowSpecs.Size.first, &m_WindowSpecs.Size.second);
					glfwGetWindowPos(m_WindowHandle, &m_WindowPosition.first, &m_WindowPosition.second);
				}

				glfwSetWindowMonitor(
					m_WindowHandle, m_PrimaryMonitorHandle,
					0, 0, current_video_mode_data->width, current_video_mode_data->height,
					current_video_mode_data->refreshRate
				);

				m_CurrentVideoMode = vm;
				break;
			}
		}
	}

	void Window::SetWindowState(WindowState ws) {
		if (m_CurrentWindowState == ws && m_Initialized)
			return;

		if ((ws & WindowState::Maximized) == WindowState::Maximized)
			glfwMaximizeWindow(m_WindowHandle);

		if ((ws & WindowState::Minimized) == WindowState::Minimized)
			glfwIconifyWindow(m_WindowHandle);

		if ((ws & WindowState::InputFocused) == WindowState::InputFocused) {
			glfwRestoreWindow(m_WindowHandle);
			glfwShowWindow(m_WindowHandle);    
			glfwFocusWindow(m_WindowHandle);     
		}

		m_CurrentWindowState = ws;
	}


	// <------------------ Functions ------------------>

	void Window::Update() {
		m_Running = !glfwWindowShouldClose(m_WindowHandle);

		glfwSwapBuffers(m_WindowHandle);
		glfwPollEvents();
	}

	void Window::Shutdown() {
		glfwSetWindowShouldClose(m_WindowHandle, true);
		m_Running = false;
	}
}