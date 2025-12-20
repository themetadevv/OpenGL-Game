#pragma once

#include "OpenGL/OpenGL.h"
#include "Objects/Sprite.h"

namespace Game {
	class ResourceManager {
	private:
		std::unordered_map<std::string, std::unique_ptr<OpenGL::Shader>>    m_Shaders;
		std::unordered_map<std::string, std::unique_ptr<OpenGL::Texture2D>> m_Textures2D;

		std::unordered_map<std::string, std::unique_ptr<OpenGL::Mesh::Quad>>      m_QuadMeshes;
		std::unordered_map<std::string, std::unique_ptr<OpenGL::Mesh::Triangle>>  m_TriangleMeshes;

		std::unordered_map<std::string, std::unique_ptr<Sprite>> m_Sprites;

		template <typename T>
		struct Resource {
			static constexpr bool m_NameRequired = false;
			static_assert(sizeof(T) == 0, "Unknown Resource Type!");
		};

		template<>
		struct Resource<OpenGL::Shader> {
			static constexpr bool m_NameRequired = true;

			static auto& Get(ResourceManager* rm) {
				return rm->m_Shaders;
			}
		};

		template<>
		struct Resource<OpenGL::Texture2D> {
			static constexpr bool m_NameRequired = true;

			static auto& Get(ResourceManager* rm) {
				return rm->m_Textures2D;
			}
		};

		template<>
		struct Resource<OpenGL::Mesh::Quad> {
			static constexpr bool m_NameRequired = false;

			static auto& Get(ResourceManager* rm) {
				return rm->m_QuadMeshes;
			}
		};

		template<>
		struct Resource<OpenGL::Mesh::Triangle> {
			static constexpr bool m_NameRequired = false;

			static auto& Get(ResourceManager* rm) {
				return rm->m_TriangleMeshes;
			}
		};

		template<>
		struct Resource<Sprite> {
			static constexpr bool m_NameRequired = true;

			static auto& Get(ResourceManager* rm) {
				return rm->m_Sprites;
			}
		};

	public:
		ResourceManager();
		~ResourceManager();

		template<typename T, typename... Args>
		void CreateResource(const std::string& resource_name, Args&&... args) {
			auto& map = Resource<T>::Get(this);
			if (!map.contains(resource_name)) {
				std::unique_ptr<T> resource;

				if constexpr (Resource<T>::m_NameRequired) {
					resource = unique(T, resource_name, std::forward<Args>(args)...);
				}
				else {
					resource = unique(T, std::forward<Args>(args)...);
				}
				
				map.emplace(resource_name, std::move(resource));
			}
		}

		template<typename T>
		T* GetResource(const std::string& resource_name) {
			auto& map = Resource<T>::Get(this);
			auto it = map.find(resource_name);
			if (it != map.end())
				return it->second.get();

			Log("Resource (Type : ", typeid(T).name(), ") -> ", resource_name, " doesnt exists!");
			return nullptr;
		}
	};
}