
#include "pch.h"

#include "Platform/OpenGL/OpenGL.h"

#include "Game.h"
#include "Sprite.h"

namespace Game {
	Sprite::Sprite(const std::string& name, Platform::OpenGL::Renderer* renderer, Platform::OpenGL::ResourceManager* resource_manager) :
		m_Renderer(renderer), m_ResourceManager(resource_manager)
	{
		m_SpriteData.Name = name;
		m_SpriteData.SpriteShader = nullptr;
		m_SpriteData.SpriteTexture = nullptr;
		m_SpriteData.Color = Vector3(1.0f);

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

		m_ResourceManager->CreateResource<Platform::OpenGL::Buffer::VertexArray>(ShaderConst::QUAD_VAO);
		m_ResourceManager->CreateResource<Platform::OpenGL::Buffer::VertexBuffer>(ShaderConst::QUAD_VBO, sizeof(float) * 4 * 4, vertices);

		m_ResourceManager->GetResource<Platform::OpenGL::Buffer::VertexArray>(ShaderConst::QUAD_VAO)->AddDataToBuffer(
			*m_ResourceManager->GetResource<Platform::OpenGL::Buffer::VertexBuffer>(ShaderConst::QUAD_VBO), 
			QuadVBL
		);

		m_ResourceManager->CreateResource<Platform::OpenGL::Buffer::IndexBuffer>(ShaderConst::QUAD_IBO, 3U * 2U, indices);

		m_ResourceManager->GetResource<Platform::OpenGL::Buffer::VertexArray>(ShaderConst::QUAD_VAO)->Unbind();
		m_ResourceManager->GetResource<Platform::OpenGL::Buffer::VertexBuffer>(ShaderConst::QUAD_VBO)->Unbind();
	}

	bool Sprite::SetShader(Platform::OpenGL::Shader* shader) {
		if (m_SpriteData.SpriteShader != shader) {
			m_SpriteData.SpriteShader = shader;
			return true;
		}
		
		std::cout << "Same Shader was Set Again!\n";
		return false;
	}

	bool Sprite::SetTexture(Platform::OpenGL::Texture2D* texture) {
		if (m_SpriteData.SpriteTexture != texture) {
			m_SpriteData.SpriteTexture = texture;
			return true;
		}

		std::cout << "Same Texture was Set Again!\n";
		return false;
	}

	void Sprite::SetSize(const Vector2& size) {
		m_SpriteData.SpriteTransform2D.Size = size;
	}

	void Sprite::SetPosition(const Vector2& position) {
		m_SpriteData.SpriteTransform2D.Position = position;
	}

	void Sprite::SetRotation(const float& rot) {
		m_SpriteData.SpriteTransform2D.Rotation = rot;
	}

	void Sprite::SetColor(const Vector3& val) {
		m_SpriteData.Color = val;
	}

	void Sprite::Draw(const Mat4& view, const Mat4& projection) {
		m_SpriteData.SpriteShader->Bind();
		
		Mat4 u_MVP = projection * view * m_SpriteData.SpriteTransform2D.GetModelMatrix();
		m_SpriteData.SpriteShader->SetUniformMat4(ShaderConst::UMVP, u_MVP);

		bool texture_attached = (m_SpriteData.SpriteTexture != nullptr);

		m_SpriteData.SpriteShader->SetUniform1i(ShaderConst::UTEX_ATTACHED, texture_attached);
		m_SpriteData.SpriteShader->SetUniform4f(ShaderConst::UCOLOR, { m_SpriteData.Color, 0.1f });

		if (m_SpriteData.SpriteTexture != nullptr) {
			m_SpriteData.SpriteTexture->Bind(0);
			m_SpriteData.SpriteShader->SetUniform1i(ShaderConst::UTEX, 0);
		}

		m_Renderer->DrawIndexed(
			m_ResourceManager->GetResource<Platform::OpenGL::Buffer::VertexArray>(ShaderConst::QUAD_VAO),
			m_ResourceManager->GetResource<Platform::OpenGL::Buffer::IndexBuffer>(ShaderConst::QUAD_IBO)
		);
	}
}