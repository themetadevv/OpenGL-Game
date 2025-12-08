#pragma once

#include "OpenGL/Buffers/VertexArray.h"
#include "OpenGL/Buffers/VertexBuffer.h"
#include "OpenGL/Buffers/IndexBuffer.h"

namespace OpenGL {
	class Renderer {
	private:
		void Initialize();
		void Shutdown();

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
			GLCall(glViewport(0, 0, width, height));
		}

	public:
		Renderer();
		~Renderer();

		void SetViewport(GLFWwindow* window_handle) const {
			glfwSetFramebufferSizeCallback(window_handle, FramebufferSizeCallback);
		}

		void Clear(const glm::vec4& color);

		void DrawArray(Buffer::VertexArray* vao);
		void DrawIndexed(Buffer::VertexArray* vao, Buffer::IndexBuffer* ibo);		
	};
}