#pragma once

#define DEFAULT_UNPACK_ALIGNMENT 4
#define INVALID_UNIFORM_LOCATION -1

inline std::string SHADER_FILE_EXTENSIONS[5] = {
	".glsl", ".shader"
	".vert", ".vertex",
	".frag", ".fragment"
};

#ifdef GL_DEBUG
	void GLClearErrors();
	const char* GLGetErrorEnumName(GLenum error_code);
	bool GLCheckError(const char* cond_name, unsigned int line, const char* file);

	#define GLCall(X) GLClearErrors(); X; if(!(GLCheckError(#X, __LINE__, __FILE__))) { __debugbreak(); }
#else
#define GLCall(X) X
#endif