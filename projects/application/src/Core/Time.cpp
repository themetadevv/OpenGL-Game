
#include "pch.h"
#include "Core/Core.h"

#include "Time.h"

namespace Core {
	double Time::m_LastTime = 0.0; 
	double Time::m_DeltaTime = 0.0;
	double Time::m_ElapsedTime = 0.0;

	int Time::m_FPS = 0;
	int Time::m_FrameCount = 0;
	double Time::m_FPSTimer = 0.0;
}