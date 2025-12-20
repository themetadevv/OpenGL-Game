
#include "pch.h"
#include "Core/Core.h"
#include "Core/Utils.h"

#include "OpenGL/OpenGL_Core.h"

#include "OpenGL/Maths.h"

#include <stb_image/stb_image.h>

#include "Texture2D.h"

namespace OpenGL {
	
	// <------------------ Static Functions ------------------>

	static uint32_t TextureFormatToGLInternalFormat(TextureFormat texture_format) {
		switch (texture_format) {
			case TextureFormat::R: return GL_R8;
			case TextureFormat::RG: return GL_RG8;
			case TextureFormat::RGB: return GL_RGB8;
			case TextureFormat::RGBA: return GL_RGBA8;
		}

		ASSERT(false, "Unknown Texture Format!");
		return 0;
	}

	static uint32_t TextureFormatToGLDataFormat(TextureFormat texture_format) {
		switch (texture_format) {
			case TextureFormat::R: return GL_RED;
			case TextureFormat::RG: return GL_RG;
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::RGBA: return GL_RGBA;
		}

		ASSERT(false, "Unknown Texture Format!");
		return 0;
	}

	// <------------------ Constructors/Deconstructor ------------------>

	Texture2D::Texture2D(const std::string& texture_name, const std::string& texture_path) :
		m_RendererID(0), m_InternalFormat(0), m_DataFormat(0), m_ImageLoaded(0), m_ImageBuffer(nullptr)
	{
		m_TextureData.Name = texture_name;
		m_TextureData.ImgFormat = ImageFormat::Unknown;
		m_TextureData.TexFormat = TextureFormat::Unknown;

		bool path_exists = std::filesystem::exists(texture_path);
		if (!path_exists) {
			LOG_ASSERT(0, std::format(
				"[Texture2D] Parsing Error : texture/image file does not exists! path -> {}",
				texture_path
			));
			return;
		}

		auto ext = Core::Utils::to_lower(std::filesystem::path(texture_path).extension().string());

		// image format check
		if (ext == ".png")
			m_TextureData.ImgFormat = ImageFormat::PNG;
		else if (ext == ".jpg")
			m_TextureData.ImgFormat = ImageFormat::JPG;
		else if (ext != ".png" || ext != ".jpg")
			m_TextureData.ImgFormat = ImageFormat::Unknown;

		// if image format is not supported by the engine then exit
		if (m_TextureData.ImgFormat == ImageFormat::Unknown) {
			LOG_ASSERT(0, "[Texture2D] : assigned texture image format is not supported by the engine!");
			return;
		}

		m_TextureData.Path = texture_path; // finaly assigning the texture path

		stbi_set_flip_vertically_on_load(true);

		int width = 0, height = 0;
		int number_of_channels = 0;

		m_ImageBuffer = stbi_load(m_TextureData.Path.c_str(), &width, &height, &number_of_channels, 0);
		if (m_ImageBuffer == nullptr) {
			LOG_ASSERT(0, std::format(
				"[Texture2D] Parsing Error : Image Buffer* is null!, texture/image file has no data! path -> {}",
				texture_path
			));
			return;
		}
			
		m_ImageLoaded = true;
		m_TextureData.Width = width;
		m_TextureData.Height = height;

		if (number_of_channels == 4) {
			m_TextureData.TexFormat = TextureFormat::RGBA;
		}
		else if (number_of_channels == 3) {
			m_TextureData.TexFormat = TextureFormat::RGB;
		}
		else if (number_of_channels == 2) {
			m_TextureData.TexFormat = TextureFormat::RG;
		}
		else if (number_of_channels == 1) {
			m_TextureData.TexFormat = TextureFormat::R;
		}

		m_InternalFormat = TextureFormatToGLInternalFormat(m_TextureData.TexFormat);
		m_DataFormat = TextureFormatToGLDataFormat(m_TextureData.TexFormat);

		ASSERT(m_InternalFormat & m_DataFormat, "Format not Supported!");

		// creating the texture

		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
		GLCall(glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_TextureData.Width, m_TextureData.Height));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureData.Width, m_TextureData.Height, m_DataFormat, GL_UNSIGNED_BYTE, m_ImageBuffer));

		// free the image buffer after use
		stbi_image_free(m_ImageBuffer);
	}

	Texture2D::Texture2D(const TextureData& texture_data) :
		m_TextureData(texture_data), m_RendererID(0U), m_InternalFormat(0U), m_DataFormat(0U), m_ImageLoaded(0), m_ImageBuffer(nullptr)
	{
		m_InternalFormat = TextureFormatToGLInternalFormat(texture_data.TexFormat);
		m_DataFormat = TextureFormatToGLDataFormat(texture_data.TexFormat);

		ASSERT(m_InternalFormat & m_DataFormat, "Format not Supported!");
		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
		GLCall(glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_TextureData.Width, m_TextureData.Height));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT));
	}

	// <------------------ Public Functions ------------------>

	void Texture2D::UploadTextureData(void* data, uint32_t size) const {
		uint32_t bpp = 0;
		if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::RGBA))
			bpp = 4;
		else if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::RGB))
			bpp = 3;
		else if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::RG))
			bpp = 2;
		else if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::R))
			bpp = 1;

		ASSERT(size == (m_TextureData.Width * m_TextureData.Height * bpp), "Data must be entire texture!");
		if (!(m_TextureData.Width * m_TextureData.Height * bpp)) {
			return;
		}

		GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureData.Width, m_TextureData.Height, m_DataFormat, GL_UNSIGNED_BYTE, data));
	}

	void Texture2D::OverrideBind(int texture_slot) const {	
		GLCall(glBindTextureUnit(texture_slot, m_RendererID));
	}
}