#pragma once

#include "Platform/OpenGL/Buffers/IndexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/VertexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexBufferLayout.h"
#include "Platform/OpenGL/Renderer/Shader.h"
#include "Platform/OpenGL/Renderer/Texture2D.h"


namespace Platform::OpenGL {
	class ResourceManager {
	private:
		std::unordered_map<std::string, std::unique_ptr<Shader>>               m_Shaders;
		std::unordered_map<std::string, std::unique_ptr<Texture2D>>	           m_Textures2D;
		std::unordered_map<std::string, std::unique_ptr<Buffer::VertexBuffer>> m_VertexBuffers;
		std::unordered_map<std::string, std::unique_ptr<Buffer::IndexBuffer>>  m_IndexBuffers;
		std::unordered_map<std::string, std::unique_ptr<Buffer::VertexArray>>  m_VertexArray;


		template <typename T>
		struct Resource {
			static constexpr bool m_NameRequired = false;
			static_assert(sizeof(T) == 0, "Unknown Resource Type!");
		};

		template<>
		struct Resource<Shader> {
			static constexpr bool m_NameRequired = true;

			static auto& Get(ResourceManager* rm) {
				return rm->m_Shaders;
			}
		};

		template<>
		struct Resource<Texture2D> {
			static constexpr bool m_NameRequired = true;

			static auto& Get(ResourceManager* rm) {
				return rm->m_Textures2D;
			}
		};

		template<>
		struct Resource<Buffer::VertexArray> {
			static constexpr bool m_NameRequired = false;

			static auto& Get(ResourceManager* rm) {
				return rm->m_VertexArray;
			}
		};

		template<>
		struct Resource<Buffer::VertexBuffer> {
			static constexpr bool m_NameRequired = false;

			static auto& Get(ResourceManager* rm) {
				return rm->m_VertexBuffers;
			}
		};

		template<>
		struct Resource<Buffer::IndexBuffer> {
			static constexpr bool m_NameRequired = false;

			static auto& Get(ResourceManager* rm) {
				return rm->m_IndexBuffers;
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
			else {
				std::cout << "Resource (Type : " << typeid(T).name() << ") -> " << resource_name << " Already exists! in Renderer" << "\n";
			}		
		}

		template<typename T>
		T* GetResource(const std::string& resource_name) {
			auto& map = Resource<T>::Get(this);
			auto it = map.find(resource_name);
			if (it != map.end())
				return it->second.get();

			std::cout << "Resource (Type : " << typeid(T).name() << ") -> " << resource_name << " Not Found! in Renderer\n";
			return nullptr;
		}
	};
}