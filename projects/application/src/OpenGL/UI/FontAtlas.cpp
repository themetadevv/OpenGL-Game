
#include "pch.h"

#include "Core/Core.h"
#include "Core/Font.h"

#include "OpenGL/OpenGL_Core.h"
#include "OpenGL/Maths.h"

#include "FontAtlas.h"

namespace OpenGL {

	// <------------------ Constructors/Deconstructor ------------------>

	FontAtlas::FontAtlas(const std::string& font_atlas_name, Core::Font* font) :
		m_Name(font_atlas_name), m_Font(font),
		m_AtlasWidth(0), m_AtlasHeight(0)
	{
		
	}

	FontAtlas::~FontAtlas() {

	}

	// <------------------ Public Functions ------------------>

		// <------------------ Setters ------------------>

	void FontAtlas::SetFont(Core::Font* font) {
		if (m_Font == font)
			return;

		m_Font = font;
	}

	void FontAtlas::UploadAtlasData() {

	}

}