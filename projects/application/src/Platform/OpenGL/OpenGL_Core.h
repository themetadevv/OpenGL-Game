#pragma once

#ifdef ENABLE_DEBUGGING
void GLClearErrors();
const char* GLGetErrorEnumName(GLenum error_code);
bool GLCheckError(const char* func_name, unsigned int func_call_line_no, const char* func_call_file_name);

	#define GLCall(X) GLClearErrors(); X; if(!(GLCheckError(#X, __LINE__, __FILE__))) { __debugbreak(); }
#else
#define GLCall(X) X
#endif