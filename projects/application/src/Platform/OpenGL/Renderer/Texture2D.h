#pragma once

// This texture class below may only work for OpenGL 4.6

namespace Platform::OpenGL {
	enum class ImageFormat {
		None = -1,
		PNG,
		JPG
	};

	enum class TextureFormat {
		None = -1,
		R,
		RG,
		RGB,
		RGBA,
	};

	struct TextureData {
		std::string Name; 
		std::string Path;

		uint32_t Width;
		uint32_t Height;

		ImageFormat ImgFormat = ImageFormat::None;
		TextureFormat TexFormat = TextureFormat::None;
	};

	uint32_t TextureFormatToGLInternalFormat(TextureFormat texture_format);
	uint32_t TextureFormatToGLDataFormat(TextureFormat texture_format);

	class Texture2D {
	private:
		TextureData m_TextureData;

		uint32_t m_RendererID; // Texture/Renderer/Buffer ID

		uint32_t m_InternalFormat; // Specifies Number of color-components in Image (Example : GL_RGBA8 (4-Floats of 8-Bits), GL_RGB8((3-Floats of 8-Bits)))
		uint32_t m_DataFormat; // Specifies Order of Data in Image (Example : GL_RGBA , GLRGB)

		bool m_ImageLoaded;
		unsigned char* m_ImageBuffer;

	public:
		Texture2D(const std::string& texture_name, const std::string& texture_image_path);
		Texture2D(const TextureData& texture_data);

		const std::string GetName() const { return m_TextureData.Name; }

		const uint32_t  GetTextureID() const { return m_RendererID; }
		const uint32_t  GetWidth() const { return m_TextureData.Width; }
		const uint32_t  GetHeight() const { return  m_TextureData.Height; }

		void SetData(void* data, uint32_t size) const;
		void Bind(int texture_slot) const;
		void Unbind() const;
	};
}

 