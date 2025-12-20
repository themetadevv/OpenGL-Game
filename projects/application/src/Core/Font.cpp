
#include "pch.h"
#include "Core/Core.h"

#include "Font.h"

namespace Core {

	// <------------------ Constructors/Deconstructor ------------------>

	Font::Font(const FontSpecification& font_spec) :
		m_FontSpecification(font_spec), m_Face(nullptr) 
	{
		LoadFont();
	}

	Font::~Font() {}

	// <------------------ Private Functions ------------------>

	bool Font::LoadFont() {
		if (FT_New_Face(FreeTypeLibrary::GetLibrary(), m_FontSpecification.Path.c_str(), m_FontSpecification.FaceIndex, &m_Face)) {
			LOG_ASSERT(0, std::format(
				"Failed to create font face! font name : {} ", m_FontSpecification.Name
			));
			return false;
		}
			

		if (FT_Set_Pixel_Sizes(m_Face, 0, m_FontSpecification.Size)) {
			LOG_ASSERT(0, std::format(
				"Failed to set font size! font name : {} ", m_FontSpecification.Name
			));
			return false;
		}

		return true;
	}

	// <------------------ Public Functions ------------------>

	bool Font::LoadCharacter(unsigned char c) {
		if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER)) {
			LOG_ASSERT(0, std::format(
				"Failed to load char : ", c
			));
			return false;
		}

		return true;
	}

	void Font::SetFontSize(int size) {
		if (m_FontSpecification.Size == size)
			return;

		m_FontSpecification.Size = size;
	}

	void Font::SetFaceIndex(int index /*= 0*/) {
		if (m_FontSpecification.FaceIndex == index)
			return;

		m_FontSpecification.FaceIndex = index;
	}

}