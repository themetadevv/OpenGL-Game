
#include "pch.h"

#include "Core/Core.h"

#include "OpenGL/Renderer/Texture2D.h"
#include "OpenGL/Maths.h"

#include "OpenGL/OpenGL_Utils.h"

#include <stb_image/stb_image_write.h>

#include "FontAtlas.h"

namespace OpenGL {

	// <------------------ Constructors/Deconstructor ------------------>

	FontAtlas::FontAtlas(const std::string& font_atlas_name, Core::Font* font) :
		m_Name(font_atlas_name), m_Font(font)
	{
		m_AtlasDimension.first = 0;
		m_AtlasDimension.second = 0;
		UploadAtlasData();
	}

	FontAtlas::~FontAtlas() {

	}

	// <------------------ Public Functions ------------------>

	void FontAtlas::UploadAtlasData() {
		struct CharacterDimension {
			unsigned int width, rows;
		};

		std::unordered_map<char, CharacterDimension> characters_dimension;
		unsigned int max_character_height = 0; 

		// looping through printable ASCII chars, 32 = space, 127 = DEL (non-printable).
		for (unsigned char c = 32; c < 127; c++) {
			if(!m_Font->LoadCharacter(c)) // load each character -> ASCII 32-126 
				continue;

			FT_Bitmap& bm = m_Font->GetFace()->glyph->bitmap; // store each character's bitmap

			// storing each character's dimensions
			characters_dimension[c] = {
				bm.width, bm.rows
			};

			// final max character height
			if (bm.rows > max_character_height)
				max_character_height = bm.rows;
		}

		unsigned int atlas_character_padding = 1;
		unsigned int atlas_row_width = 0;
		unsigned int atlas_width = 0;
		unsigned int atlas_height = max_character_height;

		// looping through each characters dimension
		for (auto& [c, c_size] : characters_dimension) {
			if (atlas_row_width + c_size.width + atlas_character_padding >= MAX_ATLAS_WIDTH) { // if the total atlas width exceeds MAX_ATLAS_WIDTH then move to new row
				atlas_height += max_character_height + atlas_character_padding; // increase atlas height on new row creation
				atlas_row_width = 0; // setting atlas row width back to 0
			}

			atlas_row_width += c_size.width + atlas_character_padding; // increasing new row width based on chracter's width + atlas_character_padding

			// final atlas width
			if (atlas_row_width > atlas_width)
				atlas_width = atlas_row_width;
		}

		m_AtlasDimension.first = atlas_width;
		m_AtlasDimension.second = atlas_height;

		unsigned int total_atlas_pixel = m_AtlasDimension.first * m_AtlasDimension.second;

		// allocating atlas_data on cpu buffer , each atlas pixel element is initialized to grayscale (0)
		std::vector<unsigned char> final_atlas_data(total_atlas_pixel, 0); // yet to be filled with data

		unsigned int pen_x = 0, pen_y = 0;
		unsigned int row_height = max_character_height;

		// Again! looping through printable ASCII chars, 32 = space, 127 = DEL (non-printable).
		for (unsigned char c = 32; c < 127; c++) {
			if(!m_Font->LoadCharacter(c))
				continue;

			FT_Bitmap& bm = m_Font->GetFace()->glyph->bitmap; // store each character's bitmap

			if (pen_x + bm.width + atlas_character_padding >= m_AtlasDimension.first) { // if the pen tries to place the character exceeding MAX_ATLAS_WIDTH then move to next row
				pen_x = 0; // moved pen x to new row
				pen_y += row_height + atlas_character_padding; // moved pen y to new row
			}

			// copying each pixel row of the character into the atlas
			for (unsigned int row = 0; row < bm.rows; row++) {
				memcpy(&final_atlas_data[(pen_y + row) * m_AtlasDimension.first + pen_x],
					&bm.buffer[row * bm.width],
					bm.width);
			}

			// pushing each character's data

			Character character_data;

			character_data.Width = bm.width;
			character_data.Height = bm.rows;
			character_data.BearingX = m_Font->GetFace()->glyph->bitmap_left;
			character_data.BearingY = m_Font->GetFace()->glyph->bitmap_top;
			character_data.Advance = m_Font->GetFace()->glyph->advance.x >> 6;

			character_data.uvMin = Vector2(
				float(pen_x) / float(m_AtlasDimension.first),
				float(pen_y + bm.rows) / float(m_AtlasDimension.second)
			);

			character_data.uvMax = Vector2(
				float(pen_x + bm.width) / float(m_AtlasDimension.first),
				float(pen_y) / float(m_AtlasDimension.second)
			);


			m_CharactersData[c] = character_data;
			
			// forwading pen position
			pen_x += bm.width + atlas_character_padding;
		}

#ifdef CONFIGURATION_DEBUG

		// creating a image with the font atlas data for debug purpose

		stbi_write_png(std::string("assets/generated/font atlases/" + m_Font->GetFontName() + ".png").c_str(),
			m_AtlasDimension.first,
			m_AtlasDimension.second, 1,                
			final_atlas_data.data(),
			m_AtlasDimension.first);

#endif

		Utils::UnPackBytesAlignment(1);

		OpenGL::TextureData glyph_tex_data;
		glyph_tex_data.Name = "GlyphTex";
		glyph_tex_data.Path = "";
		glyph_tex_data.Width = m_AtlasDimension.first;
		glyph_tex_data.Height = m_AtlasDimension.second;
		glyph_tex_data.ImgFormat = ImageFormat::Unknown;
		glyph_tex_data.TexFormat = TextureFormat::R;

		m_CharactersTexture =  unique(OpenGL::Texture2D, glyph_tex_data);
		m_CharactersTexture->UploadTextureData(final_atlas_data.data(), final_atlas_data.size());

		Utils::UnPackBytesAlignment(DEFAULT_UNPACK_ALIGNMENT);
	}

}