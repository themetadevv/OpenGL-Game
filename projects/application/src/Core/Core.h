#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef CONFIGURATION_DEBUG
	#define ENABLE_DEBUGGING
#endif

#ifdef ENABLE_DEBUGGING
	#define ENABLE_ASSERT 
	#define ENABLE_LOGGING 
#endif

#ifdef ENABLE_ASSERT

inline bool CoreCheckError(bool condition, const char* error_msg, const char* condition_name, const char* func_call_file_name, int func_call_line_no) {
	if (!condition) {
		std::cout << "\n[CORE ASSERT] Condition failed!\n";
		std::cout << "Error : " << error_msg << "\n";
		std::cout << "Condition : " << condition_name << '\n';
		std::cout << "Line : " << func_call_line_no << '\n';
		std::cout << "File : " << func_call_file_name << '\n';
		std::cout << std::endl;

		return false;
	}

	return true;
}

#define CORE_ASSERT(X, ...) if(!(CoreCheckError((X), __VA_ARGS__, #X, __FILE__, __LINE__))) { __debugbreak(); } 
#else
#define CORE_ASSERT(X) X;
#endif

#ifdef ENABLE_LOGGING

template<typename... Args>
void Log(Args&&... args) {
	std::cout << "[" << __TIME__ << "] -> ";
	(std::cout << ... << args);
	std::cout << '\n';
}

#else

template<typename... Args>
inline void Log(Args&&... args) {

}

#endif

#ifdef PLATFORM_WINDOWS 
	#define PLATFORM "Windows"
#else
#define PLATFORM "Unknown"
#endif

#define unique(T, ...) std::make_unique<T>(__VA_ARGS__)