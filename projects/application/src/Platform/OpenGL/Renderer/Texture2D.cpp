
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "Platform/OpenGL/Maths.h"

#include <stb_image.h>

#include "Texture2D.h"

namespace Platform::OpenGL {
	
	uint32_t TextureFormatToGLInternalFormat(TextureFormat texture_format) {
		switch (texture_format) {
			case TextureFormat::R: return GL_R8;
			case TextureFormat::RG: return GL_RG8;
			case TextureFormat::RGB: return GL_RGB8;
			case TextureFormat::RGBA: return GL_RGBA8;
		}

		CORE_ASSERT(false, "Unknown Texture Format!");
		return 0;
	}

	uint32_t TextureFormatToGLDataFormat(TextureFormat texture_format) {
		switch (texture_format) {
			case TextureFormat::R: return GL_R;
			case TextureFormat::RG: return GL_RG;
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::RGBA: return GL_RGBA;
		}

		CORE_ASSERT(false, "Unknown Texture Format!");
		return 0;
	}

	Texture2D::Texture2D(const std::string& texture_name, const std::string& texture_image_path) :
		 m_RendererID(0U), m_InternalFormat(0U), m_DataFormat(0U), m_ImageLoaded(0), m_ImageBuffer(nullptr)
	{
		m_TextureData.Name = texture_name;
		m_TextureData.Path = texture_image_path;
		m_TextureData.Width = 0U;
		m_TextureData.Height = 0U;
		m_TextureData.ImgFormat = ImageFormat::None;
		m_TextureData.TexFormat = TextureFormat::None;

		stbi_set_flip_vertically_on_load(true);

		int width = 0, height = 0;
		int number_of_channels = 0;

		m_ImageBuffer = stbi_load(texture_image_path.c_str(), &width, &height, &number_of_channels, 0);
		CORE_ASSERT(m_ImageBuffer, "Image Buffer* is null!");
		
		if (m_ImageBuffer != nullptr) {
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

			CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not Supported!");

			GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
			GLCall(glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_TextureData.Width, m_TextureData.Height));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT));
			GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureData.Width, m_TextureData.Height, m_DataFormat, GL_UNSIGNED_BYTE, m_ImageBuffer));

			stbi_image_free(m_ImageBuffer);
		}
	}

	Texture2D::Texture2D(const TextureData& texture_data) :
		m_TextureData(texture_data), m_RendererID(0U), m_InternalFormat(0U), m_DataFormat(0U), m_ImageLoaded(0), m_ImageBuffer(nullptr)
	{
		m_InternalFormat = TextureFormatToGLInternalFormat(texture_data.TexFormat);
		m_DataFormat = TextureFormatToGLDataFormat(texture_data.TexFormat);

		CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not Supported!");

		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
		GLCall(glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_TextureData.Width, m_TextureData.Height));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT));
	}

	void Texture2D::SetData(void* data, uint32_t size) const {
		uint32_t bpp = 0;
		if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::RGBA))
			bpp = 4;
		else if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::RGB))
			bpp = 3;
		else if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::RG))
			bpp = 2;
		else if (m_DataFormat == TextureFormatToGLDataFormat(TextureFormat::R))
			bpp = 1;

		CORE_ASSERT(size == (m_TextureData.Width * m_TextureData.Height * bpp), "Data must be entire texture!");
		GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureData.Width, m_TextureData.Height, m_DataFormat, GL_UNSIGNED_BYTE, data));
	}

	void Texture2D::Bind(int texture_slot) const {	
		GLCall(glBindTextureUnit(texture_slot, m_RendererID));
	}
}