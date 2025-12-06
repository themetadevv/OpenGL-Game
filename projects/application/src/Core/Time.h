#pragma once

namespace Core {
	class Time {
	private:
		static double m_LastTime;
		static double m_DeltaTime;
		static double m_ElapsedTime;

		static int m_FPS;
		static int m_FrameCount;
		static double m_FPSTimer;

	public:
		static void Init() {
			m_LastTime = glfwGetTime();
			CORE_ASSERT(m_LastTime, "Get Time Failed! Did you Created GLFWwindow Context ?");
		}

		static void Update() {
			double current_time = glfwGetTime();
			m_DeltaTime = current_time - m_LastTime;
			m_LastTime = current_time;
			m_ElapsedTime += m_DeltaTime;

			m_FrameCount++;
			m_FPSTimer += m_DeltaTime;

			if (m_FPSTimer >= 1.0) {
				m_FPS = m_FrameCount;
				m_FrameCount = 0;
				m_FPSTimer = 0.0;
			}
		}

		inline static double GetDeltaTime() {
			return m_DeltaTime;
		}

		inline static double GetElapsedTime() {
			return m_ElapsedTime;
		}

		inline static int GetFPS() {
			return m_FPS;
		}
	}; 
}