#pragma once

#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/VertexBuffer.h"
#include "Platform/OpenGL/Buffers/IndexBuffer.h"

namespace Platform::OpenGL {
	class Renderer {
	private:
		void Initialize();
		void Shutdown();

	public:
		Renderer();
		~Renderer();

		void Clear(const glm::vec4& color);

		void DrawArray(Buffer::VertexArray* vao);
		void DrawIndexed(Buffer::VertexArray* vao, Buffer::IndexBuffer* ibo);		
	};
}