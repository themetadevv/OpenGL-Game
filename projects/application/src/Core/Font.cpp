
#include "pch.h"
#include "Core/Core.h"

#include "Font.h"

namespace Core {

	// <------------------ Constructors/Deconstructor ------------------>

	Font::Font(const FontSpecification& font_spec) :
		m_FontSpecification(font_spec), m_FTLibrary(nullptr), m_Face(nullptr)
	{
		LoadFont();
	}

	Font::~Font() {
		FT_Done_Face(m_Face);
		FT_Done_FreeType(m_FTLibrary);
	}

	// <------------------ Private Functions ------------------>

	bool Font::LoadFont() {
		if (FT_Init_FreeType(&m_FTLibrary)) {
			Log("Failed to init freetype library!");
			return false;
		}
			
		if (FT_New_Face(m_FTLibrary, m_FontSpecification.Path.c_str(), m_FontSpecification.FaceIndex, &m_Face)) {
			Log("Failed to create font face! font name : ", m_FontSpecification.Name);
			return false;
		}
			

		if (FT_Set_Pixel_Sizes(m_Face, 0, m_FontSpecification.Size)) {
			Log("Failed to set font size! font name : ", m_FontSpecification.Name);
			return false;
		}
	}

	// <------------------ Public Functions ------------------>

	bool Font::LoadCharacter(unsigned char c) {
		if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER)) {
			Log("Failed to set load char");
			return false;
		}
	}

	void Font::SetFontSize(int size) {
		m_FontSpecification.Size = size;
	}

}