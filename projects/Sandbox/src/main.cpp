

#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "Core/Window.h"

#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/IndexBuffer.h"
#include "Platform/OpenGL/OpenGL_Shader.h"
#include "Platform/OpenGL/OpenGL_Texture.h"

#include "Platform/OpenGL/OpenGL_Renderer.h"
#include "Core/Renderer.h"


float vertices[] = {
	//   pos.xy        uv.xy
	-0.5f, -0.5f,      0.0f, 0.0f, // bottom-left 0 
	 0.5f, -0.5f,      1.0f, 0.0f, // bottom-right 1
	 0.5f,  0.5f,      1.0f, 1.0f, // top-right 2
	-0.5f,  0.5f,      0.0f, 1.0f  // top-left 3
};

unsigned int indices[]{
	0, 3, 2,
	2, 1, 0
};

int main() {
	using namespace Platform::OpenGL;

	Core::WindowData m_WindowData;
	m_WindowData.Title  = "Platform " + std::string(PLATFORM);
	m_WindowData.VSync  = false;
	m_WindowData.Width  = 1366;
	m_WindowData.Height = 768;

	std::unique_ptr<Core::IWindow> m_Window = std::unique_ptr<Core::IWindow>(Core::IWindow::CreateWindow(m_WindowData));
	std::unique_ptr<Core::IRenderer> m_Renderer = std::unique_ptr<Core::IRenderer>(Core::IRenderer::CreateRenderer());

	Shader test_shader("TestShader", "C:/shaders/test_shader.glsl");
	Texture2D test_texture("TestTexture", "C:/shaders/babee.png");
	Texture2D test_texture_1("TestTexture", "C:/shaders/babee_2.png");

	m_Renderer->AddVAO("test_vao", std::make_unique<Buffer::VertexArray>());
	m_Renderer->GetVAO("test_vao")->Bind();

	m_Renderer->AddVBO("test_vbo", std::make_unique<Platform::OpenGL::Buffer::VertexBuffer>(sizeof(vertices), vertices));
	m_Renderer->GetVBO("test_vbo")->Bind();

	Buffer::VertexBufferLayout VBL;
	VBL.Push<float>(2);
	VBL.Push<float>(2);

	m_Renderer->GetVAO("test_vao")->AddDataToBuffer(*m_Renderer->GetVBO("test_vbo"), VBL);
	m_Renderer->AddIBO("test_ibo", std::make_unique<Platform::OpenGL::Buffer::IndexBuffer>(sizeof(indices), indices));

	m_Renderer->GetVAO("test_vao")->Unbind();
	m_Renderer->GetVBO("test_vbo")->Unbind();
	m_Renderer->GetIBO("test_ibo")->Unbind();

	while (m_Window->Running()) {
		m_Renderer->Clear({ 0.3f, 0.3f, 0.3f, 1.0f });

		m_Renderer->GetVAO("test_vao")->Bind();
		m_Renderer->GetIBO("test_ibo")->Bind();

		test_shader.Bind();

		test_shader.SetUniform1i("u_Texture0", 0);
		test_shader.SetUniform1i("u_Texture1", 1);
		test_shader.SetUniform1f("u_MixAmount", 0.7f);

		test_texture.Bind(0);
		test_texture_1.Bind(1);
		
		m_Renderer->DrawIndexed(m_Renderer->GetIBO("test_ibo")->GetIndicesCount());

		m_Window->OnUpdate();
	}
}