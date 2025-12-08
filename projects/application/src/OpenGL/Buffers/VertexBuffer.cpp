
#include "pch.h"
#include "Core/Core.h"

#include "VertexBuffer.h"

#include "OpenGL/OpenGL_Core.h"

namespace OpenGL::Buffer {

	VertexBuffer::VertexBuffer(unsigned int size, const void* data) 
		: m_RendererID(0)
	{
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, NULL));
	}

	VertexBuffer::~VertexBuffer() {
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::Bind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, NULL));
	}

}