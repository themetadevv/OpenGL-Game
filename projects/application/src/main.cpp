

#include "pch.h"
#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Time.h"
#include "Core/Input.h"

#include "Objects/Sprite.h"
#include "Objects/Resource.h"

#include "OpenGL/UI/FontAtlas.h"
#include "Objects/Text.h"

#include "Core/Font.h"

// test program
int main() {
	using namespace OpenGL;

	Core::FontSpecification FontArialSpecs;
	FontArialSpecs.Name = "Arial";
	FontArialSpecs.Path = "assets/Arial.ttf";
	FontArialSpecs.FaceIndex = 0;
	FontArialSpecs.Size = 28;

	Core::FontSpecification FontRobotoSpecs;
	FontRobotoSpecs.Name = "Roboto";
	FontRobotoSpecs.Path = "assets/Roboto-Black.ttf";
	FontRobotoSpecs.FaceIndex = 0;
	FontRobotoSpecs.Size = 28;

	Core::Font* arial = new Core::Font(FontArialSpecs);
	Core::Font* roboto = new Core::Font(FontRobotoSpecs);

	Core::WindowSpecification Specs;
	Specs.Title = "Platform - " + std::string(PLATFORM) + " API - OpenGL\n";
	Specs.Size.first = 1600;
	Specs.Size.second = 900;
	Specs.VidMode = Core::VideoMode::Windowed;
	Specs.WinState = Core::WindowState::InputFocused;
	Specs.VSync = true;

	Core::Window* window = new Core::Window(Specs);
	Renderer* renderer = new Renderer();

	FontAtlas* font_atlas = new FontAtlas("ArialFontAtlas", arial);
	FontAtlas* roboto_font_atlas = new FontAtlas("RobotoFontAtlas", roboto);

	Shader* text_shader = new Shader("TextShader.GLSL", "assets/TextShader.GLSL");

	Objects::UI::TextRendererData tex_data;
	tex_data.TextFontAtlas = font_atlas;
	tex_data.TextShader = text_shader;

	Objects::UI::TextRenderer* text_renderer = new Objects::UI::TextRenderer(tex_data, renderer);

	renderer->SetViewport(window->GetWindowHandle());

	Core::Input::Init(window->GetWindowHandle());
	Core::Time::Init();

	IMesh* quad_mesh = new Mesh::Quad();
	IMesh* tri_mesh = new Mesh::Triangle();

	//Shader* mesh_shader = new Shader("MeshShader.GLSL", "assets/MeshShader.GLSL");
	Shader* mesh_shader = new Shader("MeshShader.GLSL", "assets/MeshShader.GLSL");

	Texture2D* bird_texture = new Texture2D("BirdSprite", "assets/bird.png");
	Game::Sprite* bird_sprite = new Game::Sprite("Bird");

	Mat4 view_matrix(1.0f);
	view_matrix = glm::translate(view_matrix, Vector3(300.0f, 150.0f, 0.0f));

	Mat4 projection_matrix(1.0f);
	projection_matrix = glm::ortho(0.0f, (float)window->GetWindowSize().first, 0.0f, (float)window->GetWindowSize().second, -1.0f, 1.0f);

	bird_sprite->SetShader(mesh_shader);
	bird_sprite->SetTexture(bird_texture);
	bird_sprite->SetMesh(quad_mesh);

	Vector2 birdpos(100.0f, 50.0f);
	float gravity = -200.0f; 
	float jumpVelocity = 150.0f; 
	float birdVelocity = 0.0f;


	bird_sprite->SetSize({ 50.0f,50.0f });
	Vector2 cursor_pos(1.0f);

	renderer->SetProjectionMatrix(projection_matrix);
	renderer->SetViewMatrix(view_matrix);

	Transform2D t;
	t.Size = { 1.0f , 0.0f };
	t.Position = { 100.0f, 450.0f };
	t.Rotation = 10.0f;

	Color animatedColor = Color(255.0f);

	while (window->Running()) {
		renderer->Clear({ 0.3f,0.2f,0.3f,1.0f });

		Color sprite_color = Color(255.0f);

		cursor_pos = Vector2((float)Core::Input::GetMousePosX(), (float)Core::Input::GetMousePosY());

		if (Core::Input::IsKeyPressed(KeyCode::Escape))
			window->Shutdown();

		if (Core::Input::IsKeyDown(KeyCode::W))
			birdpos.y += 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyDown(KeyCode::S))
			birdpos.y -= 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyDown(KeyCode::A))
			birdpos.x -= 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyDown(KeyCode::D))
			birdpos.x += 100.0f * (float)Core::Time::GetDeltaTime();

		if (Core::Input::IsKeyPressed(KeyCode::Space)) 
			birdVelocity = jumpVelocity;

		if (Core::Input::IsMouseButtonDown(MouseCode::Left))
			sprite_color = Color(255.0f, 0.0f, 0.0f);

		if (Core::Input::IsMouseButtonReleased(MouseCode::Left))
			sprite_color = Color(0.0f, 255.0f, 0.0f, 150.0f);

		if (Core::Input::IsKeyPressed(KeyCode::F11)) {
			window->SetVideoMode(Core::VideoMode::Fullscreen);
		}
			
		if (Core::Input::IsKeyPressed(KeyCode::F10)) {
			window->SetVideoMode(Core::VideoMode::Borderless);
		}

		if (Core::Input::IsKeyPressed(KeyCode::F9)) {
			window->SetVideoMode(Core::VideoMode::Windowed);
		}

		float time = (float)Core::Time::GetElapsedTime();

		float alpha = (std::sin(time * 6.0f) + 1.0f) * 0.5f * (255.0f - 50.0f) + 50.0f;

		text_renderer->SetFontAtlas(font_atlas);
		text_renderer->DrawText("Frame Count : " + std::to_string(Core::Time::GetFPS()), { 100.0f, 450.0f }, 1.0f, Color(255, 0, 0));
		text_renderer->DrawText("Elapsed Time : " + std::to_string(Core::Time::GetElapsedTime()), { 100.0f, 500.0f }, 1.0f, Color(0, 255, 0));
		text_renderer->DrawText("Delta Time : " + std::to_string(Core::Time::GetDeltaTime()), { 100.0f, 550.0f }, 1.0f, Color(0, 0, 100));
		text_renderer->DrawText("Video Mode : " + window->GetCurrentVideoModeString(), {100.0f, 600.0f}, 1.0f, Color(0, 255, 0));

		//text_renderer->SetFontAtlas(roboto_font_atlas);
		text_renderer->DrawText("Space to flap", {100.0f, 400.0f}, 1.0f, Color(0, 255, 0, alpha));

		birdVelocity += gravity * Core::Time::GetDeltaTime();
		birdpos.y += birdVelocity * Core::Time::GetDeltaTime();

		bird_sprite->SetPosition(birdpos);
		bird_sprite->SetColor(sprite_color);
		bird_sprite->Draw(renderer);

		Core::Input::Update();
		Core::Time::Update();
		window->Update();
	}

	window->Shutdown();
	Core::FreeTypeLibrary::Shutdown();

	delete window;
	delete renderer;
	delete quad_mesh;
	delete tri_mesh;
	delete mesh_shader;
	delete bird_texture;
	delete bird_sprite;
	delete arial;
	delete roboto;
	delete font_atlas;
	delete roboto_font_atlas;
}