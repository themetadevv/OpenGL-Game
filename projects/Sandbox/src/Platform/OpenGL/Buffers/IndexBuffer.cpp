
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "IndexBuffer.h"

namespace Platform::OpenGL::Buffer {
	IndexBuffer::IndexBuffer(unsigned int indices_count, const void* data)
		: m_RendererID(0), m_IndicesCount(indices_count) 
	{
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_count, data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() {
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::Bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::Unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL));
	}
}