#pragma once

#ifdef CONFIGURATION_DEBUG
	#define ENABLE_DEBUGGING 1
#endif

#ifdef ENABLE_DEBUGGING
	#define ENABLE_ASSERT 1
	#define ENABLE_LOGGING 1
#endif

#ifdef ENABLE_ASSERT
//#include "Logger.h"
	#define CORE_ASSERT(X, ...) if(!(X)) { __debugbreak(); }
#else
#define CORE_ASSERT(X)
#endif

#ifdef PLATFORM_WINDOWS 
	#define PLATFORM "Windows"
#else
#define PLATFORM "Unknown"
#endif

#define PLATFORM_OPENGL

#ifdef PLATFORM_OPENGL
	#define RENDERING_API_GL
#elif PLATFORM_DX11
	#define RENDERING_API_DX11
#else
#define RENDERING_API_NONE
#endif
