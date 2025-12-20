
#include "pch.h"
#include "Core/Core.h"

#include "Core/Utils.h"

#include "OpenGL/OpenGL_Core.h"
#include "Shader.h"

namespace OpenGL {
	enum struct ShaderParseStage {
		None = -1,
		Vertex,
		Fragment
	};

	// <------------------ Constructors/Deconstructor ------------------>

	Shader::Shader(RoString shader_name, RoString shader_src_path) : 
		m_RendererID(NULL), m_ShaderLoaded(false),  m_ShaderBound(false) 
	{
		std::stringstream shader_data[3];

		// shader file path check
		if (!std::filesystem::exists(std::filesystem::path(shader_src_path))) {
			LOG_ASSERT(0, std::format(
				"[Shader] Parsing Error : shader file does not exists! path -> {}", 
				shader_src_path				
			));

			return;
		}		 

		std::ifstream shader_file_content {
			std::filesystem::path(shader_src_path)
		};

		// shader file open status check
		if (!shader_file_content.is_open()) {
			LOG_ASSERT(0, std::format(
				"[Shader] Parsing Error : failed to open shader file! path -> {}",
				shader_src_path
			));

			return;
		}

		std::string line;
		ShaderParseStage shader_parse_stage = ShaderParseStage::None;
		while (getline(shader_file_content, line)) {
			if (line.find("// VERTEX") != std::string::npos) {
				shader_parse_stage = ShaderParseStage::Vertex;
				continue;
			}

			if (line.find("// FRAGMENT") != std::string::npos) {
				shader_parse_stage = ShaderParseStage::Fragment;
				continue;
			}

			// shader parse stage check
			if (shader_parse_stage == ShaderParseStage::None) {
				LOG_ASSERT(0, std::format(
					"[Shader] Parsing Error : unknown shader stage! make sure '// VERTEX' and '// FRAGMENT' was passed! path -> {}",
					shader_src_path
				));

				return;
			}

			shader_data[(int)shader_parse_stage] << line << '\n';
		}

		m_ShaderData.Name = shader_name;
		m_ShaderData.Path = shader_src_path;
		m_ShaderData.VertexShaderSource = shader_data[(int)ShaderParseStage::Vertex].str();
		m_ShaderData.FragmentShaderSource = shader_data[(int)ShaderParseStage::Fragment].str();

		if(CompileShader()) 
			m_ShaderLoaded = true;
	}

	Shader::Shader(RoString shader_name, RoString vertex_shader_src_path, RoString fragment_shader_src_path) :
		m_RendererID(NULL), m_ShaderLoaded(false), m_ShaderBound(false) 
	{
		
	}

	Shader::~Shader() {
		if(m_RendererID)
			GLCall(glDeleteProgram(m_RendererID));
	}

	// <------------------ Private Functions ------------------>


	bool Shader::CompileShader() {
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

			std::string gl_log = vertex_shader_compile_status_logs;
			while (!gl_log.empty() && (gl_log.back() == '\n' || gl_log.back() == '\r'))
				gl_log.pop_back();

			LOG_ASSERT(0, std::format(
				"[Shader] Compile Error : failed to compile VERTEX section of the shader! name -> '{}', path -> '{}'\nLogs -> {}",
				m_ShaderData.Name, m_ShaderData.Path, gl_log
			));

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

			std::string gl_log = fragment_shader_compile_status_logs;
			while (!gl_log.empty() && (gl_log.back() == '\n' || gl_log.back() == '\r'))
				gl_log.pop_back();

			LOG_ASSERT(0, std::format(
				"[Shader] Compile Error : failed to compile FRAGMENT section of the shader! name -> '{}', path -> '{}'\n| GL Logs -> {} ",
				m_ShaderData.Name, m_ShaderData.Path, gl_log
			));

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

			std::string gl_log = shader_program_link_status_logs;
			while (!gl_log.empty() && (gl_log.back() == '\n' || gl_log.back() == '\r'))
				gl_log.pop_back();

			LOG_ASSERT(0, std::format(
				"[Shader] Linking Error : failed to link the shader! name -> '{}', path -> '{}',| GL Logs -> {} \n",
				m_ShaderData.Name, m_ShaderData.Path, gl_log
			));

			return false;
		}

		GLCall(glDeleteShader(vertex_shader_id));
		GLCall(glDeleteShader(fragment_shader_id));

		return true;
	}

	// <------------------ Public Functions ------------------>

	void Shader::Bind() {
		if (!m_ShaderBound) {
			GLCall(glUseProgram(m_RendererID));
			m_ShaderBound = true;
		}
	}

	void Shader::Unbind() {
		if (m_ShaderBound) {
			GLCall(glUseProgram(NULL));
			m_ShaderBound = false;
		}
	}

	int Shader::GetCachedUniformLocation(const std::string& uniform_name) {
		if (!ShaderBound()) {
			LOG_ASSERT(0, std::format(
				"[Shader] Error : bind the shader '{}' before setting the uniform '{}'", 
				m_ShaderData.Name, uniform_name
			));
			return INVALID_UNIFORM_LOCATION;
		}

		if (m_StoredUniforms.find(uniform_name) != m_StoredUniforms.end())
			return m_StoredUniforms[uniform_name];

		GLCall(int loc = glGetUniformLocation(m_RendererID, uniform_name.c_str()));
		if (loc == INVALID_UNIFORM_LOCATION) {
			LOG_ASSERT(0, std::format(
				"[Shader] Error : failed to locate uniform '{}' in shader '{}'",
				uniform_name, m_ShaderData.Name
			));
			return INVALID_UNIFORM_LOCATION;
		}

		m_StoredUniforms[uniform_name] = loc;
		return loc;
	}
}
