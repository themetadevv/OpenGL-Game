
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "stb_image/stb_image.h"

#include "Texture2D.h"

namespace Platform::OpenGL {
	Texture2D::Texture2D(const std::string& texture_name, const std::string& texture_path) 
		: m_RendererID(0), m_LocalTexBuffer(nullptr)
	{
		CORE_ASSERT(ParseTexture(texture_name, texture_path), "Failed to Parse Texture");
	}

	Texture2D::~Texture2D() {
		GLCall(glDeleteTextures(1, &m_TextureData.ID));
	}

	bool Texture2D::ParseTexture(const std::string& texture_name, const std::string& texture_path) {
		stbi_set_flip_vertically_on_load(true);

		m_LocalTexBuffer = stbi_load(texture_path.c_str(), (int*)&m_TextureData.TexWidth, (int*)&m_TextureData.TexHeight, (int*)&m_TextureData.TexBPP, 4);

		if (m_LocalTexBuffer == nullptr) {
			std::cout << "Failed to load texture" << texture_name << "Path : " << texture_path << '\n';
			return false;
		}

		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_TextureData.TexWidth, m_TextureData.TexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalTexBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		m_TextureData.ID   = m_RendererID;
		m_TextureData.Name = texture_name;
		m_TextureData.Path = texture_path;

		if (m_LocalTexBuffer) {
			stbi_image_free(m_LocalTexBuffer);
		}	

		return true;
	}

	void Texture2D::Bind(unsigned int tex_slot) const {
		GLCall(glActiveTexture(GL_TEXTURE0 + tex_slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureData.ID));
	}

	void Texture2D::Unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}