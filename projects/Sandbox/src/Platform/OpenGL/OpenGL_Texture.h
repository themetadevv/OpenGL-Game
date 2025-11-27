#pragma once


namespace Platform::OpenGL {

	struct TextureData {
		std::string Name, Path;
		unsigned int ID, TexWidth, TexHeight, TexBPP;
	};

	class Texture2D {
	private:
		unsigned int m_RendererID;
		unsigned char* m_LocalTexBuffer;
		TextureData m_TextureData;

		bool ParseTexture(const std::string& texture_name, const std::string& texture_path);

	public:
		Texture2D(const std::string& texture_name, const std::string& texture_path);
		~Texture2D();

		void Bind(unsigned int tex_slot) const;
		void Unbind() const;

		inline const TextureData& GetTextureData() const {
			return m_TextureData;
		}
	};
}

 