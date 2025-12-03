

#include "pch.h"
#include "Core/Core.h"
#include "Core/Window.h"

#include "Platform/OpenGL/OpenGL.h"

#include "Game/Game.h"
#include "Game/Sprite.h"

float vertices[] = {
			0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f
};

unsigned int indices[] = {
	0, 3, 2,
	2, 1, 0
};

int main() {
	using namespace Platform::OpenGL;

	std::unique_ptr<Renderer> m_Renderer = unique(Renderer);
	//Renderer* m_Renderer = new Renderer();
	std::unique_ptr<ResourceManager> m_ResourceManager = unique(ResourceManager);
	//ResourceManager* m_ResourceManager = new ResourceManager();

	Core::WindowData m_WindowData;
	m_WindowData.Title = "Platform - " + std::string(PLATFORM) + " API - OpenGL\n";
	m_WindowData.VSync  = true;
	m_WindowData.Width  = 1366;
	m_WindowData.Height = 768;

	std::unique_ptr<Core::IWindow> m_Window = std::unique_ptr<Core::IWindow>(Core::IWindow::CreateWindow(m_WindowData));
	
	m_ResourceManager->CreateResource<Shader>("SpriteShader", "C:/shaders/sprite_shader.glsl");
	auto SpriteShader = m_ResourceManager->GetResource<Shader>("SpriteShader");

	m_ResourceManager->CreateResource<Texture2D>("QuadTexture0", "C:/shaders/babee.png");
	m_ResourceManager->CreateResource<Texture2D>("QuadTexture1", "C:/shaders/babee_2.png");
	m_ResourceManager->CreateResource<Texture2D>("QuadTexture2", "C:/shaders/babee_3.png");
	auto QuadTexture0 = m_ResourceManager->GetResource<Texture2D>("QuadTexture0");
	auto QuadTexture1 = m_ResourceManager->GetResource<Texture2D>("QuadTexture1");
	auto QuadTexture2 = m_ResourceManager->GetResource<Texture2D>("QuadTexture2");


	Game::Sprite* m_Sprite = new Game::Sprite("Test", m_Renderer.get(), m_ResourceManager.get());
	m_Sprite->SetShader(SpriteShader);
	m_Sprite->SetTexture(QuadTexture2);
	
	Mat4 view = Mat4(1.0f);
	view = glm::translate(view, Vector3(300.0f, 150.0f, 0.0f));

	Mat4 projection = Mat4(1.0f);
	projection = glm::ortho(0.0f, 1366.0f, 0.0f, 768.0f, -1.0f, 1.0f);
	
	float x_val = 400.0f;

	while (m_Window->Running()) {
		m_Renderer->Clear({ 0.3f, 0.3f, 0.3f, 1.0f });

		x_val -= 1.0f;

		m_Sprite->SetPosition({ x_val, 50.0f });
		m_Sprite->SetRotation(0.0f);
		m_Sprite->SetSize({ 347.0f, 484.0f });
		m_Sprite->SetColor(Vector3(1.f, 0.0f, 0.0f));

		m_Sprite->Draw(view, projection);

		m_Window->OnUpdate();
	}
}