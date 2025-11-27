#pragma once

#include "Core/Renderer.h"

namespace Platform::OpenGL {
	class OpenGL_Renderer : public Core::IRenderer {
	private:
		std::unordered_map<std::string, std::unique_ptr<Buffer::VertexBuffer>> m_VertexBuffers;
		std::unordered_map<std::string, std::unique_ptr<Buffer::IndexBuffer>>  m_IndexBuffers;
		std::unordered_map<std::string, std::unique_ptr<Buffer::VertexArray>>  m_VertexArray;

	public:

		OpenGL_Renderer() {
			this->Initialize();
		}

		void Initialize() override;
		void Shutdown() override;

		void Clear(const glm::vec4& color) override;
		void DrawIndexed(unsigned int index_count) override;

		void AddVBO(const std::string& name, std::unique_ptr<Buffer::VertexBuffer> vbo) override;
		void AddVAO(const std::string& name, std::unique_ptr<Buffer::VertexArray> vao)  override;
		void AddIBO(const std::string& name, std::unique_ptr<Buffer::IndexBuffer> ibo)  override;

		Platform::OpenGL::Buffer::VertexBuffer* GetVBO(const std::string& name) const override;
		Platform::OpenGL::Buffer::VertexArray*  GetVAO(const std::string& name) const override;
		Platform::OpenGL::Buffer::IndexBuffer*  GetIBO(const std::string& name) const override;

		inline Core::RenderAPI GetAPI() const override {
			return Core::RenderAPI::OPENGL;
		}
	};
}