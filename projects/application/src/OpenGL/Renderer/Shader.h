#pragma once

#include "OpenGL/Maths.h"

namespace ShaderConst {
	constexpr char UMVP[] = "u_MVP";
	constexpr char UCOLOR[] = "u_Color";
	constexpr char UTEX[] = "u_Texture";
	constexpr char UTEX_ATTACHED[] = "u_TextureAttached";
}

// basic shader class impl

namespace OpenGL {
	struct ShaderData {
		std::string Name;
		std::string Path;
		std::string VertexShaderSource;
		std::string FragmentShaderSource;
	};

	class Shader {
	private:
		// <------------------ Private Members ------------------>

		enum class UniformType {
			None = -1,
			Float,
			Mat4,
			Vector2,
			Vector3,
			Vector4,
		};

		uint32_t m_RendererID;
		ShaderData m_ShaderData;

		bool m_ShaderLoaded;
		bool m_ShaderBound;

		std::unordered_map<std::string, int> m_StoredUniforms;

		template <typename T>
		using Uniform= std::conditional_t<std::is_arithmetic_v<T>, T, const T&>;

	public:
		// <------------------ Constructors/Deconstructor ------------------>

		Shader(RoString shader_name, RoString shader_src_path);
		Shader(RoString shader_name, RoString vertex_shader_src_path, RoString fragment_shader_src_path);

		~Shader();

	private:
		// <------------------ Private Functions ------------------>

		bool CompileShader();

	public:
		// <------------------ Public Functions ------------------>

		void Bind();
		void Unbind();

		// <------------------ Getters ------------------>

		RoString GetShaderName() const { return m_ShaderData.Name; }
		RoString GetVertexShaderSource() const { return m_ShaderData.VertexShaderSource; }
		RoString GetFragmentShaderSource() const { return m_ShaderData.FragmentShaderSource; }

		bool ShaderBound() const { return m_ShaderBound; }

		int GetCachedUniformLocation(const std::string& uniform_name);

		// <------------------ Setters ------------------>

		template <typename T>
		void SetUniform(const std::string& uniform_name, Uniform<T> value) {
			int loc = GetCachedUniformLocation(uniform_name);

			if constexpr (std::is_same_v<T, int>) {
				GLCall(glUniform1i(loc, value));
			}

			else if constexpr (std::is_same_v<T, float>) {
				GLCall(glUniform1f(loc, value));
			}
				
			else if constexpr (std::is_same_v<T, Vector2>) {
				GLCall(glUniform2f(loc, value.x, value.y));
			}
				
			else if constexpr (std::is_same_v<T, Vector3>) {
				GLCall(glUniform3f(loc, value.x, value.y, value.z));
			}
				
			else if constexpr (std::is_same_v<T, Vector4>) {
				GLCall(glUniform4f(loc, value.x, value.y, value.z, value.w));
			}
				
			else if constexpr (std::is_same_v<T, Mat4>) {
				GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value)));
			}
				
			else {
				static_assert(false, "Unsupported  uniform type!");
			}				
		}
	};
}