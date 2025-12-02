#pragma once

#include "Platform/OpenGL/Maths.h"

namespace Platform::OpenGL {
	enum struct ShaderType {
		NONE = -1,
		VERTEX, FRAGMENT
	};

	struct ShaderData {
		std::string Name;
		std::string VertexShaderSource;
		std::string FragmentShaderSource;
	};
	
	class Shader {
	private:
		unsigned int m_RendererID;
		ShaderData m_ShaderData;
		std::unordered_map<std::string, int> m_UniformCache;

		const bool ParseShader(const std::string& shader_name, const std::string& shader_path);
		const bool CompileShader();
		const int GetCachedUniformLocation(const std::string& uniform_name);

	public:

		Shader(const std::string& shader_name, const std::string& shader_path);
		~Shader();

		const ShaderData& GetShaderData() const {
			return m_ShaderData;
		}

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, const glm::vec2& value);
		void SetUniform3f(const std::string& name, const glm::vec3& value);
		void SetUniform4f(const std::string& name, const glm::vec4& value);
		void SetUniformMat4(const std::string& name, const glm::mat4x4& value);

	};
}