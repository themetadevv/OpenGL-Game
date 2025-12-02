
#include "pch.h"

#include "Core/Core.h"
#include "Core/Window.h"

#include "Platform/OpenGL/OpenGL_Core.h"
#include "Platform/OpenGL/Maths.h"

#include "Renderer.h"

namespace Platform::OpenGL {
	Renderer::Renderer() {
		Initialize();
	}

	Renderer::~Renderer() {
		Shutdown();
	}

	void Renderer::Initialize() {
		
	}

	void Renderer::Shutdown() {
		
	}

	void Renderer::Clear(const glm::vec4& color) {
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Renderer::DrawIndexed(Buffer::VertexArray* vao, unsigned int index_count) {
		vao->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr));
	}

}
