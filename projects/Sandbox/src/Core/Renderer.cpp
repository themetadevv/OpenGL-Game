
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"
#include "Platform/OpenGL/Buffers/IndexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/VertexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexBufferLayout.h"
#include "Platform/OpenGL/OpenGL_Renderer.h"

#include "Core/Window.h"

#include "Renderer.h"

namespace Core {
	IRenderer* IRenderer::CreateRenderer() {
#ifdef RENDERING_API_GL
		return new Platform::OpenGL::OpenGL_Renderer();
#elif RENDERING_API_DX11
#error CURRENTLY DX11 API IS NOT SUPPORTED
#elif RENDERING_API_NONE
#error CURRENTLY NONE API IS DEFINED
#endif
	}
}