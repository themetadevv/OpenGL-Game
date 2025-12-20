#pragma once

#include "Core/Font.h"

namespace OpenGL {

	constexpr static unsigned int MAX_ATLAS_WIDTH = 256;

	struct Character {
		Vector2 uvMin;
		Vector2 uvMax;
		uint32_t Width;
		uint32_t Height;
		uint32_t BearingX;
		uint32_t BearingY;
		uint32_t Advance;
	};

	class FontAtlas {
	private:
		// <------------------ Private Members ------------------>

		// FontAtlas Specifications
		std::string m_Name;
		Core::Font* m_Font;

		std::pair<uint32_t, uint32_t> m_AtlasDimension;

		std::unique_ptr<OpenGL::Texture2D> m_CharactersTexture;
		std::unordered_map<char, Character> m_CharactersData;

	public:
		// <------------------ Constructors/Deconstructor ------------------>

		FontAtlas(const std::string& font_atlas_name, Core::Font* font);
		~FontAtlas();

	public:
		// <------------------ Public Functions ------------------>

		// <------------------ Setters ------------------>

		// <------------------ Getters ------------------>

		std::string GetAtlasName() const { return m_Name; }
		std::string GetAtlasFontName() const { return m_Font->GetFontName(); }

		const Character& GetCharacterData(char c) const { return m_CharactersData.at(c); }
		Texture2D* GetCharacterTexture() const { return m_CharactersTexture.get(); }

		std::pair<uint32_t, uint32_t> GetAtlasDimension() const { return m_AtlasDimension; }

	private:
		// <------------------ Private Functions ------------------>

		// ts made me cry, should not be called in a loop (this func is heavy asf)
		void UploadAtlasData();
	};
}