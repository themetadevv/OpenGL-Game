#pragma once


namespace Platform::OpenGL::Buffer {
	class IndexBuffer {
	private:
		unsigned int m_RendererID;
		unsigned int m_IndicesCount;
	public:
		IndexBuffer(unsigned int indices_count, const void* data);
		~IndexBuffer();

		inline const unsigned int& GetIndicesCount() const {
			return m_IndicesCount;
		}

		void Bind() const;
		void Unbind() const;
	};
}