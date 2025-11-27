
#include "pch.h"
#include "Core/Core.h"

#include "OpenGL_Core.h"

#include "OpenGL_Shader.h"

namespace Platform::OpenGL {
	const bool Shader::ParseShader(const std::string& shader_name, const std::string& shader_path) {
		std::stringstream shader_source[2];
		bool all_shaders_section_parsed = false;
		std::ifstream shader_file_content(shader_path);

		if (!shader_file_content.is_open()) {
			CORE_ASSERT(NULL, "Failed to open shader file!");
			return false;
		}

		std::string line;
		m_CurrentShaderType = ShaderType::NONE;

		while (getline(shader_file_content, line)) {
			if (line.find("//SECTION_VERTEX") != std::string::npos) {
				m_CurrentShaderType = ShaderType::VERTEX;
				continue;
			}

			if (line.find("//SECTION_FRAGMENT") != std::string::npos) {
				m_CurrentShaderType = ShaderType::FRAGMENT;
				continue;
			}

			if (m_CurrentShaderType == ShaderType::NONE) {
				std::cout << "Unknown Shader Type was bound!\n";
				return false;
			}

			shader_source[(int)m_CurrentShaderType] << line << '\n';
		}

		m_ShaderData = ShaderData(shader_name, shader_source[0].str(), shader_source[1].str());
		return true;
	}

	const bool Shader::CompileShader() {
		const char* vertex_shader_source = m_ShaderData.VertexShaderSource.c_str();
		const char* fragment_shader_source = m_ShaderData.FragmentShaderSource.c_str();

		GLCall(unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
		GLCall(glShaderSource(vertex_shader_id, 1, &vertex_shader_source, nullptr));
		GLCall(glCompileShader(vertex_shader_id));
		int vertex_shader_compile_status_id;
		char vertex_shader_compile_status_logs[512];
		GLCall(glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &vertex_shader_compile_status_id));
		if (!vertex_shader_compile_status_id) {
			GLCall(glGetShaderInfoLog(vertex_shader_id, sizeof(vertex_shader_compile_status_logs), nullptr, vertex_shader_compile_status_logs));
			std::cout << "Failed to compile vertex section of shader : " << m_ShaderData.Name << '\n' << "Logs -> \n" << vertex_shader_compile_status_logs << '\n';
			return false;
		}

		GLCall(unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
		GLCall(glShaderSource(fragment_shader_id, 1, &fragment_shader_source, nullptr));
		GLCall(glCompileShader(fragment_shader_id));
		int fragment_shader_compile_status_id;
		char fragment_shader_compile_status_logs[512];
		GLCall(glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &fragment_shader_compile_status_id));
		if (!fragment_shader_compile_status_id) {
			GLCall(glGetShaderInfoLog(fragment_shader_id, sizeof(fragment_shader_compile_status_logs), nullptr, fragment_shader_compile_status_logs));
			std::cout << "Failed to compile fragment section of shader : " << m_ShaderData.Name << '\n' << "Logs -> \n" << fragment_shader_compile_status_logs << '\n';
			return false;
		}

		m_RendererID = glCreateProgram();
		GLCall(glAttachShader(m_RendererID, vertex_shader_id));
		GLCall(glAttachShader(m_RendererID, fragment_shader_id));
		glLinkProgram(m_RendererID);
		int shader_program_link_status_id;
		char shader_program_link_status_logs[512];
		GLCall(glGetProgramiv(m_RendererID, GL_LINK_STATUS, &shader_program_link_status_id));
		if (!shader_program_link_status_id) {
			GLCall(glGetProgramInfoLog(m_RendererID, sizeof(shader_program_link_status_logs), nullptr, shader_program_link_status_logs));
			std::cout << "Failed to link shader : " << m_ShaderData.Name << '\n' << "Logs -> \n" << shader_program_link_status_logs << '\n';
			return false;
		}

		GLCall(glDeleteShader(vertex_shader_id));
		GLCall(glDeleteShader(fragment_shader_id));

		return true;
	}

	const int Shader::GetCachedUniformLocation(const std::string& uniform_name) {
		if (m_UniformCache.find(uniform_name) != m_UniformCache.end())
			return m_UniformCache[uniform_name];

		GLCall(int uniform_location = glGetUniformLocation(m_RendererID, uniform_name.c_str()));
		if (uniform_location == -1) {
			std::cout << std::endl;
			std::cout << "Failed to locate uniform : " << uniform_name << '\n';
		}

		m_UniformCache[uniform_name] = uniform_location;

		return uniform_location;
	}

	Shader::Shader(const std::string& shader_name, const std::string& shader_path) : m_RendererID(NULL) {
		if (!ParseShader(shader_name, shader_path)) {
			std::cout << "Failed to parse shader : " << shader_name << ", " << shader_path << '\n';
		}

		CompileShader();
	}

	Shader::~Shader() {
		GLCall(glDeleteProgram(m_RendererID));
	}


	void Shader::Bind() const {
		GLCall(glUseProgram(m_RendererID));
	}

	void Shader::Unbind() const {
		GLCall(glUseProgram(NULL));
	}

	void Shader::SetUniform1i(const std::string& name, int value) {
		GLCall(glUniform1i(GetCachedUniformLocation(name), value));
	}

	void Shader::SetUniform1f(const std::string& name, float value) {
		GLCall(glUniform1f(GetCachedUniformLocation(name), value));
	}

	void Shader::SetUniform2f(const std::string& name, const glm::vec2& value) {
		GLCall(glUniform2f(GetCachedUniformLocation(name), value.x, value.y));
	}

	void Shader::SetUniform3f(const std::string& name, const glm::vec3& value) {
		GLCall(glUniform3f(GetCachedUniformLocation(name), value.x, value.y, value.z));
	}

	void Shader::SetUniform4f(const std::string& name, const glm::vec4& value) {
		GLCall(glUniform4f(GetCachedUniformLocation(name), value.x, value.y, value.z, value.w));
	}

	void Shader::SetUniformMat4(const std::string& name, const glm::mat4x4& value) {
		GLCall(glUniformMatrix4fv(GetCachedUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
	}

}
