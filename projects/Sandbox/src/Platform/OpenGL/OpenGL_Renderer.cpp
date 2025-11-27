
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "Platform/OpenGL/Buffers/IndexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/VertexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexBufferLayout.h"

#include "Core/Window.h"

#include "OpenGL_Renderer.h"

namespace Platform::OpenGL {


	void OpenGL_Renderer::Initialize() {

	}

	void OpenGL_Renderer::Shutdown() {
		m_VertexBuffers.clear();
		m_IndexBuffers.clear();
		m_VertexArray.clear();
	}

	void OpenGL_Renderer::Clear(const glm::vec4& color) {
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void OpenGL_Renderer::DrawIndexed(unsigned int index_count) {
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGL_Renderer::AddVBO(const std::string& name, std::unique_ptr<Buffer::VertexBuffer> vbo) {
		if (!m_VertexBuffers.contains(name))
			m_VertexBuffers.emplace(name, std::move(vbo));
		else
			std::cout << "VBO (" << name << ") already exists! in Renderer\n";
	}

	void OpenGL_Renderer::AddVAO(const std::string& name, std::unique_ptr<Buffer::VertexArray> vao) {
		if(!m_VertexArray.contains(name))
			m_VertexArray.emplace(name, std::move(vao));
		else
			std::cout << "VAO (" << name << ") already exists! in Renderer\n";
	}

	void OpenGL_Renderer::AddIBO(const std::string& name, std::unique_ptr<Buffer::IndexBuffer> ibo) {
		if(!m_IndexBuffers.contains(name))
			m_IndexBuffers.emplace(name, std::move(ibo));
		else
			std::cout << "IBO (" << name << ") already exists! in Renderer\n";
	}

	Buffer::VertexBuffer* OpenGL_Renderer::GetVBO(const std::string& name) const {
		auto it = m_VertexBuffers.find(name);
		return (it != m_VertexBuffers.end()) ? it->second.get() : nullptr;
	}

	Buffer::VertexArray* OpenGL_Renderer::GetVAO(const std::string& name) const {
		auto it = m_VertexArray.find(name);
		return (it != m_VertexArray.end()) ? it->second.get() : nullptr;
	}

	Buffer::IndexBuffer* OpenGL_Renderer::GetIBO(const std::string& name) const {
		auto it = m_IndexBuffers.find(name);
		return (it != m_IndexBuffers.end()) ? it->second.get() : nullptr;
	}

	

}
