#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Platform::OpenGL::Buffer {
	class VertexArray {
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddDataToBuffer(const VertexBuffer& vbo, const VertexBufferLayout& vbl);

		void Bind() const;
		void Unbind() const;
	};
}