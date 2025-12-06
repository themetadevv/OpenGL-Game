

#include "pch.h"
#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Time.h"
#include "Core/Input.h"

#include "Platform/Windows/WindowsWindow.h"

#include "Game/Level.h"
#include "Game/Sprite.h"
#include "Game/Utils/ResManager.h"

#include <free_type.h>

// test program
int main() {
	using namespace Platform::OpenGL;

	Core::WindowData Specs;
	Specs.Title = "Platform - " + std::string(PLATFORM) + " API - OpenGL\n";
	Specs.Width = 1600;
	Specs.Height = 900;
	Specs.VSync = true;

	Core::IWindow* window = new Platform::Windows::Window(Specs);
	Renderer* renderer = new Renderer();

	Core::Input::Init(static_cast<GLFWwindow*>(window->GetWindowHandle().handle));
	Core::Time::Init();

	IMesh* quad_mesh = new Mesh::Quad();
	IMesh* tri_mesh = new Mesh::Triangle();

	Shader* mesh_shader = new Shader("MeshShader.GLSL", "assets/MeshShader.GLSL");

	Texture2D* bird_texture = new Texture2D("BirdTexture", "assets/bird.png");
	Game::Sprite* bird_sprite = new Game::Sprite("Bird", renderer);

	Mat4 view_matrix(1.0f);
	view_matrix = glm::translate(view_matrix, Vector3(300.0f, 150.0f, 0.0f));

	Mat4 projection_matrix(1.0f);
	projection_matrix = glm::ortho(0.0f, (float)window->GetWindowData().Width, 0.0f, (float)window->GetWindowData().Height, -1.0f, 1.0f);

	bird_sprite->SetShader(mesh_shader);
	bird_sprite->SetTexture(bird_texture);
	bird_sprite->SetMesh(quad_mesh);

	Vector2 birdpos(100.0f, 50.0f);
	float gravity = -200.0f; 
	float jumpVelocity = 150.0f; 
	float birdVelocity = 0.0f;


	bird_sprite->SetSize({ 50.0f,50.0f });
	Vector2 cursor_pos(1.0f);

	while (window->Running()) {
		renderer->Clear({ 0.3f,0.2f,0.3f,1.0f });

		Color sprite_color = Color(255.0f);

		cursor_pos = Vector2((float)Core::Input::GetMousePosX(), (float)Core::Input::GetMousePosY());
		//std::cout << "Cursor Pos (X, Y) : " << cursor_pos.x << ", " << cursor_pos.y << '\n';

		if (Core::Input::IsKeyPressed(KeyCode::Escape))
			window->OnShutdown();

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

		birdVelocity += gravity * Core::Time::GetDeltaTime();
		birdpos.y += birdVelocity * Core::Time::GetDeltaTime();

		// draw
		bird_sprite->SetPosition(birdpos);
		bird_sprite->SetColor(sprite_color);
		bird_sprite->SetMVP(view_matrix, projection_matrix);

		float right = bird_sprite->GetPosition().x + bird_sprite->GetSize().x;
		float left = bird_sprite->GetPosition().x;
		float bottom = bird_sprite->GetPosition().y;
		float top = bird_sprite->GetPosition().y + bird_sprite->GetSize().y;

		float windowW = window->GetWindowData().Width;
		float windowH = window->GetWindowData().Height;

		if (right >= windowW || left <= 0.0f || bottom <= 0.0f || top >= windowH) {
			std::cout << "Bird Died\n";
		}

		bird_sprite->Draw();

		Core::Input::Update();
		Core::Time::Update();
		window->OnUpdate();
	}

	delete window;
	delete renderer;
	delete quad_mesh;
	delete tri_mesh;
	delete mesh_shader;
	delete bird_texture;
	delete bird_sprite;
}