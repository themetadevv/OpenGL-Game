#pragma once

// This texture class below may only work for OpenGL 4.6

namespace OpenGL {
	enum class ImageFormat {
		Unknown = -1,
		PNG,
		JPG
	};

	enum class TextureFormat {
		Unknown = -1,
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

		ImageFormat ImgFormat;
		TextureFormat TexFormat;
	};

	inline static std::string GetImageExtensionStringFromImageFormat(ImageFormat img_fmt) {
		switch (img_fmt) {
			case OpenGL::ImageFormat::Unknown: return "Unsupported Format!"; break;
			case OpenGL::ImageFormat::PNG: return ".png"; break;
			case OpenGL::ImageFormat::JPG: return ".jpg"; break;
		}
	}

	class Texture2D {
	private:
		// <------------------ Private Members ------------------>

		TextureData m_TextureData;

		uint32_t m_RendererID; // Texture/Renderer/Buffer ID

		uint32_t m_InternalFormat; // Specifies Number of color-components in Image (Example : GL_RGBA8 (4-Floats of 8-Bits), GL_RGB8((3-Floats of 8-Bits)))
		uint32_t m_DataFormat; // Specifies Order of Data in Image (Example : GL_RGBA , GLRGB)

		bool m_ImageLoaded;
		unsigned char* m_ImageBuffer;

	public:
		// <------------------ Constructors/Deconstructor ------------------>

		Texture2D(const std::string& texture_name, const std::string& texture_path);
		Texture2D(const TextureData& texture_data);

	public:
		// <------------------ Public Functions ------------------>

		// <------------------ Setters ------------------>

		// <------------------ Getters ------------------>

		const uint32_t  GetTextureID() const { return m_RendererID; }
		const uint32_t  GetWidth() const { return m_TextureData.Width; }
		const uint32_t  GetHeight() const { return  m_TextureData.Height; }
		const std::string GetName() const { return m_TextureData.Name; }

		// <------------------ Functions ------------------>

		void UploadTextureData(void* data, uint32_t size) const;
		void OverrideBind(int texture_slot) const;
	};
}

 