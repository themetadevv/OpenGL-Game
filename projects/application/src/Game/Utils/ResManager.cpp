
#include "pch.h"
#include "Core/Core.h"

#include "ResManager.h"

namespace Game {

	ResourceManager::ResourceManager() {
		
	}

	ResourceManager::~ResourceManager() {
		m_Shaders.clear();
		m_Textures2D.clear();
	}
}