#pragma once

namespace Core {
	enum class RenderAPI {
		NONE = 0,
		OPENGL,
		DX11
	};

	class IRenderer {
	public:
		virtual ~IRenderer() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown()   = 0;

		virtual void Clear(const glm::vec4& color) = 0;
		virtual void DrawIndexed(unsigned int index_count) = 0;

		virtual void AddVBO(const std::string& name, std::unique_ptr<Platform::OpenGL::Buffer::VertexBuffer> vbo) = 0;
		virtual void AddVAO(const std::string& name, std::unique_ptr<Platform::OpenGL::Buffer::VertexArray> vao) = 0;
		virtual void AddIBO(const std::string& name, std::unique_ptr<Platform::OpenGL::Buffer::IndexBuffer> ibo) = 0;

		virtual Platform::OpenGL::Buffer::VertexBuffer* GetVBO(const std::string& name) const = 0;
		virtual Platform::OpenGL::Buffer::VertexArray*  GetVAO(const std::string& name) const = 0;
		virtual Platform::OpenGL::Buffer::IndexBuffer*  GetIBO(const std::string& name) const = 0;

		virtual inline RenderAPI GetAPI() const = 0;

		static IRenderer* CreateRenderer();
	};
}