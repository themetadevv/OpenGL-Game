#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef PLATFORM_WINDOWS 
   #define PLATFORM "Windows"
#else
   #define PLATFORM "Unknown"
#endif

#ifdef CONFIGURATION_DEBUG
	#define ENABLE_ASSERT 
	#define ENABLE_LOGGING
	#define GL_DEBUG
#endif

#define unique(T, ...) std::make_unique<T>(__VA_ARGS__)

using RoString = std::string_view;

const char* GetFileName(const char* path);
bool CoreCheckError(bool condition, RoString error_msg, const char* condition_name, const char* func_call_file_name, int func_call_line_no);

// assert macro

#ifdef ENABLE_ASSERT
#define ASSERT(X, ...) \
	do {					\
		if(!(CoreCheckError(X, __VA_ARGS__, #X, __FILE__, __LINE__))) { \
			__debugbreak();												\
		}																\
	} while (0)													
#else

#define CORE_ASSERT(X, ...) do { X; } while (0)

#endif

#ifdef ENABLE_LOGGING

inline void TempLog(RoString msg) {
	std::cout << "[Temp Log] [" << __TIME__ << "] -> ";
	std::cout << msg << '\n';
}

#else

void TempLog(RoString msg) {
	
}

#endif

// log + assert macro

#define LOG_ASSERT(cond, msg)                                       \
    do {                                                            \
        ASSERT(cond, msg);	/*  stripped out in release build */	\
        if (!(cond)) {                                              \
            std::cout << "[Log] [" << __TIME__ << "] "              \
                      << __FILE__ << ":" << __LINE__ << " -> "      \
                      << (msg) << '\n';                             \
        }                                                           \
    } while (0)