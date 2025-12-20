#pragma once

namespace OpenGL::Objects::UI {
	struct TextRendererData {
		FontAtlas* TextFontAtlas;
		Shader* TextShader;
	};

	struct TextVertex {
		Vector2 Position;
		Vector2 UV;
	};

	class TextRenderer {
	private:
		Renderer* m_Renderer;
		TextRendererData m_TextRendererData;

		Buffer::VertexBufferLayout vbl;
		std::unique_ptr<Buffer::VertexBuffer> m_VBO;
		std::unique_ptr<Buffer::VertexArray>  m_VAO;

	public:
		TextRenderer(const TextRendererData& text_renderer_data, Renderer* renderer);
		~TextRenderer();

		void SetFontAtlas(FontAtlas* font_atlas);
		void SetShader(Shader* shader);

		bool DrawText(const std::string& text = "SampleText", std::pair<float, float> position = {1.0f, 1.0f}, float scale = 1.0f, const Color& text_color = Color());
	};
}