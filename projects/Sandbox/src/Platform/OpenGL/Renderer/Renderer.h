#pragma once

#include "Platform/OpenGL/ResourceManager.h"
#include "Platform/OpenGL/Buffers/VertexBuffer.h"

namespace Platform::OpenGL {
	class Renderer {
	private:
		void Initialize();
		void Shutdown();

	public:
		Renderer();
		~Renderer();

		void Clear(const glm::vec4& color);
		void DrawIndexed(Buffer::VertexArray* vao, unsigned int index_count);
	};
}