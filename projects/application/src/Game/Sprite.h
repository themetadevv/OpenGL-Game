#pragma once

#include "OpenGL/OpenGL.h"

namespace Game {
	struct SpriteData {
		std::string Name;

		OpenGL::Shader*    Shader;
		OpenGL::Texture2D* Texture;
		OpenGL::IMesh*     Mesh;

		Color SpriteColor;
		Transform2D Transform;
		
		SpriteData() :
			Name("Defualt_Sprite"), Shader(nullptr),
			Texture(nullptr), SpriteColor(),
			Transform(), Mesh(nullptr)
		{}
	};

	class Sprite {
	private:
		OpenGL::Renderer* m_Renderer;
		SpriteData m_SpriteData;

	public:
		Sprite(const std::string& name, OpenGL::Renderer* renderer);

		void ClearShader();
		void ClearTexture();
		void ClearMesh();

		bool SetShader(OpenGL::Shader* shader);
		bool SetTexture(OpenGL::Texture2D* texture);
		bool SetMesh(OpenGL::IMesh* mesh);

		void SetSize(const Vector2& size);
		void SetPosition(const Vector2& position);
		void SetRotation(const float& rot);
		void SetColor(const Color& val);

		void SetMVP(const Mat4& view, const Mat4& projection);

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
			CORE_ASSERT(m_SpriteData.Shader, ("No! Shader was Bound in Sprite -> " + m_SpriteData.Name + "\n").c_str());
			return m_SpriteData.Shader;
		}

		inline const OpenGL::Texture2D* GetBoundTexture() const {
			CORE_ASSERT(m_SpriteData.Texture, ("No! Texture was Bound in Sprite -> " + m_SpriteData.Name + "\n").c_str());
			return m_SpriteData.Texture;
		}

		inline const Mat4 GetSpriteTransfMatrix() {
			return m_SpriteData.Transform.GetModelMatrix();
		}

		void Draw();
	};
}

