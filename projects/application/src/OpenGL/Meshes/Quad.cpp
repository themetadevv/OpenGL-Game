
#include "pch.h"
#include "Core/Core.h"

#include "OpenGL/OpenGL.h"
#include "Quad.h"

namespace OpenGL::Mesh {
	Quad::Quad() :
		m_MeshType(MeshType::Quad), m_MeshID(GenerateMeshID())
	{
		float vertices[] = {
			0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 3, 2,
			2, 1, 0
		};

		Buffer::VertexBufferLayout VBL;
		VBL.Push<float>(2);
		VBL.Push<float>(2);

		m_VAO = unique(Buffer::VertexArray);
		m_VBO = unique(Buffer::VertexBuffer, sizeof(vertices), vertices);

		m_VAO->AddDataToBuffer(*m_VBO, VBL);

		m_IBO = unique(Buffer::IndexBuffer, 3U * 2U, indices);

		m_VAO->Unbind();
		m_VBO->Unbind();
	}
}