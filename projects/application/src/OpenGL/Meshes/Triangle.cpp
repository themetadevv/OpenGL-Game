
#include "pch.h"
#include "Core/Core.h"

#include "Triangle.h"

namespace OpenGL::Mesh {
	Triangle::Triangle() 
		: m_MeshType(MeshType::Triangle), m_MeshID(GenerateMeshID())
	{
		float vertices[] = {
			// pos.x, pos.y, u, v
			0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
			1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
			0.5f, 1.0f, 0.5f, 1.0f  // top-center
		};

		Buffer::VertexBufferLayout VBL;
		VBL.Push<float>(2);
		VBL.Push<float>(2);

		m_VAO = unique(Buffer::VertexArray);
		m_VBO = unique(Buffer::VertexBuffer, sizeof(vertices), vertices);

		m_VAO->AddDataToBuffer(*m_VBO, VBL);

		m_VAO->Unbind();
		m_VBO->Unbind();
	}
}