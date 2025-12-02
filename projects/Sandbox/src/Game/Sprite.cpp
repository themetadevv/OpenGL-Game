
#include "pch.h"



#include "Sprite.h"

namespace Game {
	Sprite::Sprite(Platform::OpenGL::Renderer* renderer, Platform::OpenGL::ResourceManager* resource_manager) :
		m_Renderer(renderer), m_ResourceManager(resource_manager), m_Shader(nullptr)
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

		Platform::OpenGL::Buffer::VertexBufferLayout QuadVBL;
		QuadVBL.Push<float>(2);
		QuadVBL.Push<float>(2);

		m_ResourceManager->CreateResource<Platform::OpenGL::Buffer::VertexArray>("SpriteVAO");
		m_VAO = m_ResourceManager->GetResource<Platform::OpenGL::Buffer::VertexArray>("SpriteVAO");
		m_VAO->Bind();

		m_ResourceManager->CreateResource<Platform::OpenGL::Buffer::VertexBuffer>("SpriteVBO", sizeof(float) * 4 * 4, vertices);
		m_VBO = m_ResourceManager->GetResource<Platform::OpenGL::Buffer::VertexBuffer>("SpriteVBO");
		m_VBO->Bind();	
		
		m_VAO->AddDataToBuffer(*m_VBO, QuadVBL);

		m_ResourceManager->CreateResource<Platform::OpenGL::Buffer::IndexBuffer>("SpriteIBO", 3U * 2U, indices);
		m_IBO = m_ResourceManager->GetResource<Platform::OpenGL::Buffer::IndexBuffer>("SpriteIBO");
		
		m_VAO->Unbind();
		m_VBO->Unbind();
	}

	void Sprite::SetShader(Platform::OpenGL::Shader* shader) {
		m_Shader = shader;
	}

	void Sprite::SetSize(const Vector2& size) {
		m_Transform2D.Size = size;
	}

	void Sprite::SetPosition(const Vector2& position) {
		m_Transform2D.Position = position;
	}

	void Sprite::SetRotation(const float& radians) {
		m_Transform2D.Rotation = radians;
	}

	void Sprite::AddTexture(Platform::OpenGL::Texture2D* texture) {
		if (std::find(m_Textures.begin(), m_Textures.end(), texture) == m_Textures.end()) {
			m_Textures.push_back(texture);
		}
	}

	void Sprite::Draw(const Mat4& view, const Mat4& projection) {
		m_Shader->Bind();
		
		Mat4 u_MVP = projection * view * m_Transform2D.GetModelMatrix();

		m_Shader->SetUniformMat4(UMVP, u_MVP);

		for (unsigned int i = 0; i < m_Textures.size(); i++) {
			m_Textures[i]->Bind(i);
			m_Shader->SetUniform1i(std::string(UTEX) + std::to_string(i), i);
		}

		m_Shader->SetUniform1f("u_MixAmount", 0.7f);

		m_Renderer->DrawIndexed(m_VAO, m_IBO->GetIndicesCount());
	}
}