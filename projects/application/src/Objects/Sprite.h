#pragma once

#include "OpenGL/OpenGL.h"

namespace Game {
	struct SpriteData {
		std::string Name;

		OpenGL::Shader*    SpriteShader;
		OpenGL::Texture2D* Texture;
		OpenGL::IMesh*     Mesh;

		Color SpriteColor;
		Transform2D Transform;
		
		SpriteData() :
			Name(""), SpriteShader(nullptr),
			Texture(nullptr), SpriteColor(),
			Transform(), Mesh(nullptr)
		{}
	};

	class Sprite {
	private:
		SpriteData m_SpriteData;

	public:
		Sprite(const std::string& name);

		void SetShader(OpenGL::Shader* shader);
		void SetTexture(OpenGL::Texture2D* texture);
		void SetMesh(OpenGL::IMesh* mesh);

		void SetSize(const Vector2& size);
		void SetPosition(const Vector2& position);
		void SetRotation(const float& rot);
		void SetColor(const Color& val);

		inline const Vector2& GetSize() const {
			return m_SpriteData.Transform.Size;
		}

		inline const Vector2& GetPosition() const {
			return m_SpriteData.Transform.Position;
		}

		inline const float& GetRotation() const {
			return m_SpriteData.Transform.Rotation;
		}

		inline const std::string& GetSpriteName() const {
			return m_SpriteData.Name;
		}

		inline const OpenGL::Shader* GetBoundShader() const {
			ASSERT(m_SpriteData.SpriteShader, ("No! Shader was Bound in Sprite -> " + m_SpriteData.Name + "\n").c_str());
			return m_SpriteData.SpriteShader;
		}

		inline const OpenGL::Texture2D* GetBoundTexture() const {
			ASSERT(m_SpriteData.Texture, ("No! Texture was Bound in Sprite -> " + m_SpriteData.Name + "\n").c_str());
			return m_SpriteData.Texture;
		}

		inline const Mat4 GetSpriteTransfMatrix() {
			return m_SpriteData.Transform.GetModelMatrix();
		}

		void Draw(OpenGL::Renderer* m_Renderer);
	};
}

