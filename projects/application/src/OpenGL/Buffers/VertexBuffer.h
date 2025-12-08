#pragma once


namespace OpenGL::Buffer {
	class VertexBuffer {
	private:
		unsigned int m_RendererID;
	public:
		VertexBuffer(unsigned int size, const void* data);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}