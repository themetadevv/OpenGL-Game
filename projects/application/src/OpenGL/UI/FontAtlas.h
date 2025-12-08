#pragma once

namespace OpenGL {
	struct Character {
		glm::vec2 uvMin;
		glm::vec2 uvMax;
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
		uint32_t m_AtlasWidth;
		uint32_t m_AtlasHeight;

		std::unordered_map<char, Character> m_CharacterCollection;

	public:
		// <------------------ Constructors/Deconstructor ------------------>

		FontAtlas(const std::string& font_atlas_name, Core::Font* font);
		~FontAtlas();

	public:
		// <------------------ Public Functions ------------------>

		// <------------------ Setters ------------------>

		void SetFont(Core::Font* font);

		// <------------------ Getters ------------------>

		std::string GetAtlasName() const { return m_Name; }
		std::string GetAtlasFontName() const { m_Font->GetFontName(); }

	private:
		// <------------------ Private Functions ------------------>

		// ts made me cry
		void UploadAtlasData();
	};
}