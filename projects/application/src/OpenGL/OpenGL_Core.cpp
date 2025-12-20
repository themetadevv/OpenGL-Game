
#include "pch.h"
#include "Core/Core.h"

#include "Core/Console.h"

#include "OpenGL_Core.h"

void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

const char* GLGetErrorEnumName(GLenum error_code) {
	switch (error_code) {
		case GL_NO_ERROR			: return "NO ERROR!"; break;
		case GL_INVALID_ENUM		: return "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE		: return "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION	: return "GL_INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY		: return "GL_OUT_OF_MEMORY"; break;
		case GL_STACK_UNDERFLOW		: return "GL_STACK_UNDERFLOW"; break;
		case GL_STACK_OVERFLOW		: return "GL_STACK_OVERFLOW"; break;

		case GL_INVALID_FRAMEBUFFER_OPERATION: 
			return "GL_INVALID_FRAMEBUFFER_OPERATION"; break;

		default : return "NO ERROR!"; 
			break;
	}
}

bool GLCheckError(const char* cond_name, unsigned int line, const char* file) {
	while (GLenum error_code = glGetError()) {
		ResetConsoleStyle();
		SetConsoleStyle(ConsoleTextStyle::Cyan);
		std::cout << "\n<--- " << "GL_DEBUG" << " ----------------------------->\n";

		SetConsoleStyle(ConsoleTextStyle::White);
		std::cout << "| Condition : ";

		SetConsoleStyle(ConsoleTextStyle::Green);
		std::cout << cond_name << "\n";

		SetConsoleStyle(ConsoleTextStyle::White);
		std::cout << "| Location  : ";

		SetConsoleStyle(ConsoleTextStyle::Blue | ConsoleTextStyle::Bold);
		std::cout << GetFileName(file) << ":" << line << "\n";

		SetConsoleStyle(ConsoleTextStyle::White);
		std::cout << "| Message   : ";

		SetConsoleStyle(ConsoleTextStyle::Yellow);
		std::cout << GLGetErrorEnumName(error_code) << "\n";

		SetConsoleStyle(ConsoleTextStyle::Cyan);
		std::cout << "<--------------------------------------------------->\n";

		return false;
	}

	return true;
}