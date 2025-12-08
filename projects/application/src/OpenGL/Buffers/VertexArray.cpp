
#include "pch.h"
#include "Core/Core.h"

#include "OpenGL/OpenGL_Core.h"

#include "VertexArray.h"

namespace OpenGL::Buffer {
	
	VertexArray::VertexArray() {
		GLCall(glGenVertexArrays(1, &m_RendererID));
	}

	VertexArray::~VertexArray() {
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void VertexArray::AddDataToBuffer(const VertexBuffer& vbo, const VertexBufferLayout& vbl) {
		Bind();
		vbo.Bind();
		const auto& vbo_layout_elements = vbl.GetVertexBufferLayoutElement();

		unsigned int offset = 0;

		for (unsigned int i = 0; i < vbo_layout_elements.size(); i++) {
			const auto& element = vbo_layout_elements[i];

			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.Size, element.Type, element.Normalized, vbl.GetStrideCount(), (const void*)offset));

			offset += VertexBufferLayoutElement::GetSizeOfType(element.Type) * element.Size;
		}	
	}

	void VertexArray::Bind() const {
		GLCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() const {
		GLCall(glBindVertexArray(NULL));
	}

}