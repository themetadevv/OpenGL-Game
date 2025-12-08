
#include "pch.h"

#include "Core/Core.h"
#include "Core/Window.h"

#include "OpenGL/OpenGL_Core.h"
#include "OpenGL/Maths.h"

#include "Renderer.h"

namespace OpenGL {
	Renderer::Renderer() {
		Initialize();
	}

	Renderer::~Renderer() {
		Shutdown();
	}

	void Renderer::Initialize() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::cout << "Renderer Initialized ->\n";
		std::cout << "Vendor:   " << glGetString(GL_VENDOR) << "\n";
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
		std::cout << "Version:  " << glGetString(GL_VERSION) << "\n";
	}

	void Renderer::Shutdown() {
		
	}

	void Renderer::Clear(const glm::vec4& color) {
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Renderer::DrawArray(Buffer::VertexArray* vao) {
		vao->Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
	}

	void Renderer::DrawIndexed(Buffer::VertexArray* vao, Buffer::IndexBuffer* ibo) {
		vao->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ibo->GetIndicesCount(), GL_UNSIGNED_INT, nullptr));
	}

}
