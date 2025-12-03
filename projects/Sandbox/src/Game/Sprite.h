#pragma once

#include "Platform/OpenGL/Maths.h"

namespace Game {
	struct SpriteData {
		std::string Name;
		Platform::OpenGL::Shader* SpriteShader;
		Platform::OpenGL::Texture2D* SpriteTexture;
		Vector3 Color;
		Transform2D SpriteTransform2D;
	};

	class Sprite {
	private:
		Platform::OpenGL::Renderer* m_Renderer;
		Platform::OpenGL::ResourceManager* m_ResourceManager;

		SpriteData m_SpriteData;
	public:
		Sprite(const std::string& name, Platform::OpenGL::Renderer* renderer, Platform::OpenGL::ResourceManager* resource_manager);

		bool SetShader(Platform::OpenGL::Shader* shader);
		bool SetTexture(Platform::OpenGL::Texture2D* texture);

		void SetSize(const Vector2& size);
		void SetPosition(const Vector2& position);
		void SetRotation(const float& rot);
		
		void SetColor(const Vector3& val);

		inline const std::string& GetSpriteName() const {
			return m_SpriteData.Name;
		}

		inline const Platform::OpenGL::Shader* GetBoundShader() const {
			return m_SpriteData.SpriteShader;
		}

		inline const Platform::OpenGL::Texture2D* GetBoundTexture() const {
			CORE_ASSERT(m_SpriteData.SpriteTexture, "No! Texture was Bound in Sprite\n");
			return m_SpriteData.SpriteTexture;

		}

		inline const Mat4 GetSpriteTransfMatrix() {
			return m_SpriteData.SpriteTransform2D.GetModelMatrix();
		}

		void Draw(const Mat4& view, const Mat4& projection);
	};
}

