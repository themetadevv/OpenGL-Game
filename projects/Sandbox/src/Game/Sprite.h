#pragma once

#include "Platform/OpenGL/OpenGL.h"
#include "Platform/OpenGL/Maths.h"

namespace Game {
	class Sprite {
	private:
		Platform::OpenGL::Renderer* m_Renderer;
		Platform::OpenGL::ResourceManager* m_ResourceManager;

		Platform::OpenGL::Shader* m_Shader;
		std::vector<Platform::OpenGL::Texture2D*> m_Textures;

		Platform::OpenGL::Buffer::VertexArray* m_VAO;
		Platform::OpenGL::Buffer::VertexBuffer* m_VBO;
		Platform::OpenGL::Buffer::IndexBuffer* m_IBO;

		Transform2D m_Transform2D;
	public:
		Sprite(Platform::OpenGL::Renderer* renderer, Platform::OpenGL::ResourceManager* resource_manager);

		void SetShader(Platform::OpenGL::Shader* shader);

		void SetSize(const Vector2& size);
		void SetPosition(const Vector2& position);
		void SetRotation(const float& radians);

		void AddTexture(Platform::OpenGL::Texture2D* texture);

		void Draw(const Mat4& view, const Mat4& projection);

		inline Mat4 GetSpriteTransfMatrix() {
			return m_Transform2D.GetModelMatrix();
		}

	};
}

