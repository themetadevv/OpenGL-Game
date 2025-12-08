
#include "pch.h"
#include "Core/Core.h"

#include "OpenGL_Core.h"

void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

const char* GLGetErrorEnumName(GLenum error_code) {
	switch (error_code) {
		case GL_NO_ERROR			: return "NO ERROR!"; break;
		case GL_INVALID_ENUM		: return "INVALID ENUM!"; break;
		case GL_INVALID_VALUE		: return "INVALID VALUE!"; break;
		case GL_INVALID_OPERATION	: return "INVALID OPERATION!"; break;
		case GL_OUT_OF_MEMORY		: return "OUT OF MEMORY!"; break;
		case GL_STACK_UNDERFLOW		: return "STACK UNDERFLOW!"; break;
		case GL_STACK_OVERFLOW		: return "STACK OVERFLOW!"; break;

		case GL_INVALID_FRAMEBUFFER_OPERATION: 
			return "INVALID FRAMEBUFFER OPERATION!"; break;

		default : return "NO ERROR!"; 
			break;
	}
}

bool GLCheckError(const char* func_name, unsigned int func_call_file_name, const char* in_file) {
	while (GLenum error_code = glGetError()) {
		std::cout << std::endl;
		std::cout << "OpenGL Error Occured!\n";
		std::cout << "Enum : " << GLGetErrorEnumName(error_code) << '\n';
		std::cout << "Function : " << func_name << '\n';
		std::cout << "Line : " << func_call_file_name << '\n';
		std::cout << "File : " << in_file << '\n';
		std::cout << std::endl;

		return false;
	}

	return true;
}