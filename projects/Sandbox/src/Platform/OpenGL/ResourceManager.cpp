
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "ResourceManager.h"

namespace Platform::OpenGL {

	ResourceManager::ResourceManager() {
		
	}

	ResourceManager::~ResourceManager() {
		m_Shaders.clear();
		m_Textures2D.clear();
		m_VertexBuffers.clear();
		m_IndexBuffers.clear();
		m_VertexArray.clear();
	}
}