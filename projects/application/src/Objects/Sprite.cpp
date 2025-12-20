
#include "pch.h"
#include "Core/Core.h"

#include "Sprite.h"

namespace Game {
	Sprite::Sprite(const std::string& name)
	{
		m_SpriteData.Name = name;
	}

	void Sprite::SetShader(OpenGL::Shader* shader) {
		LOG_ASSERT(shader != nullptr, std::format(
			"Sprite::SetShader called with null shader! sprite name -> {} ", m_SpriteData.Name
		));

		if (shader == nullptr)
			return;

		if (m_SpriteData.SpriteShader == shader)
			return;

		m_SpriteData.SpriteShader = shader;
	}

	void Sprite::SetTexture(OpenGL::Texture2D* texture) {
		LOG_ASSERT(texture != nullptr, std::format(
			"Sprite::SetTexture called with null texture! sprite name -> {} ", m_SpriteData.Name
		));

		if (texture == nullptr)
			return;

		if (m_SpriteData.Texture == texture)
			return;

		m_SpriteData.Texture = texture;
	}

	void Sprite::SetMesh(OpenGL::IMesh* mesh) {
		LOG_ASSERT(mesh != nullptr, std::format(
			"Sprite::SetMesh called with null mesh! sprite name -> {} ", m_SpriteData.Name
		));

		if (mesh == nullptr)
			return;

		if (m_SpriteData.Mesh == mesh)
			return;

		m_SpriteData.Mesh = mesh;
	}

	void Sprite::SetSize(const Vector2& size) {
		m_SpriteData.Transform.Size = size;
	}

	void Sprite::SetPosition(const Vector2& position) {
		m_SpriteData.Transform.Position = position;
	}

	void Sprite::SetRotation(const float& rot) {
		m_SpriteData.Transform.Rotation = rot;
	}

	void Sprite::SetColor(const Color& val) {
		m_SpriteData.SpriteColor = val;
	}

	void Sprite::Draw(OpenGL::Renderer* r) {
		m_SpriteData.SpriteShader->Bind();
		
		bool texture_attached = (m_SpriteData.Texture != nullptr);

		m_SpriteData.SpriteShader->SetUniform<int>(ShaderConst::UTEX_ATTACHED, texture_attached);
		m_SpriteData.SpriteShader->SetUniform<Vector4>(ShaderConst::UCOLOR, { m_SpriteData.SpriteColor.R, m_SpriteData.SpriteColor.G, m_SpriteData.SpriteColor.B, m_SpriteData.SpriteColor.A });

		Mat4 u_MVP = r->GetProjectionMatrix() * r->GetViewMatrix() * m_SpriteData.Transform.GetModelMatrix();
		m_SpriteData.SpriteShader->SetUniform<Mat4>(ShaderConst::UMVP, u_MVP);

		if (m_SpriteData.Texture != nullptr) {
			m_SpriteData.Texture->OverrideBind(0);
			m_SpriteData.SpriteShader->SetUniform<int>(ShaderConst::UTEX, 0);
		}

		if (m_SpriteData.Mesh->GetMeshType() == OpenGL::MeshType::Quad) {
			r->DrawIndexed(
				m_SpriteData.Mesh->GetVAO(),
				m_SpriteData.Mesh->GetIBO()
			);
		}
		else if (m_SpriteData.Mesh->GetMeshType() == OpenGL::MeshType::Triangle) {
			r->DrawArray(m_SpriteData.Mesh->GetVAO());
		}

		m_SpriteData.SpriteShader->Unbind();
	}
}