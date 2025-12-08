#pragma once

#include "OpenGL/Renderer/Mesh.h"

namespace OpenGL::Mesh {
	class Triangle : public IMesh {
	private:
		uint32_t m_MeshID;
		MeshType m_MeshType;
		std::unique_ptr<Buffer::VertexArray>  m_VAO;
		std::unique_ptr<Buffer::VertexBuffer> m_VBO;

	public:
		Triangle();

		inline const MeshType& GetMeshType() const override {
			return m_MeshType;
		}

		inline const uint32_t& GetMeshID() const override {
			return m_MeshID;
		}

		inline Buffer::VertexArray* GetVAO() const override {
			return m_VAO.get();
		}
	};
}