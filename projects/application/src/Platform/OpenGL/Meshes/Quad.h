#pragma once

#include "Platform/OpenGL/Renderer/Mesh.h"

namespace Platform::OpenGL::Mesh {
	class Quad : public IMesh {
	private:
		uint32_t m_MeshID;
		MeshType m_MeshType;
		std::unique_ptr<Buffer::VertexArray>  m_VAO;
		std::unique_ptr<Buffer::VertexBuffer> m_VBO;
		std::unique_ptr<Buffer::IndexBuffer>  m_IBO;

	public:
		Quad();

		inline const MeshType& GetMeshType() const override {
			return m_MeshType;
		}

		inline const uint32_t& GetMeshID() const override {
			return m_MeshID;
		}

		inline Buffer::VertexArray* GetVAO() const override {
			return m_VAO.get();
		}

		inline Buffer::IndexBuffer* GetIBO() const override {
			return m_IBO.get();
		}
	};
}