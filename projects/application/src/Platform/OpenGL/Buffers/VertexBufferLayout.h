#pragma once

#include "VertexBuffer.h"

namespace Platform::OpenGL::Buffer {
	struct VertexBufferLayoutElement {
		unsigned int Size;
		unsigned int Type;
		unsigned char Normalized;

		const static unsigned int GetSizeOfType(unsigned int type) {
			switch (type)
			{
				case GL_FLOAT:			return 4; break;
				case GL_UNSIGNED_INT:	return 4; break;
				case GL_UNSIGNED_BYTE:  return 1; break;
				default:				return 0; break;
			}
		}
	};
	
	class VertexBufferLayout {
	private:
		std::vector<VertexBufferLayoutElement> m_LayoutElement;
		unsigned int m_StrideCount;
	public:
		VertexBufferLayout() : m_StrideCount(NULL) {

		}

		template <typename T>
		void Push(unsigned int count) {
			static_assert(false, "Unsupported Type!");
		}

		inline const std::vector<VertexBufferLayoutElement>& GetVertexBufferLayoutElement() const {
			return m_LayoutElement;
		}

		inline const unsigned int& GetStrideCount() const {
			return m_StrideCount;
		}
	};

	template<>
	inline void VertexBufferLayout::Push<float>(unsigned int element_size) {
		m_LayoutElement.push_back({ element_size, GL_FLOAT, GL_FALSE });
		m_StrideCount += VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT) * element_size;
	}

	template<>
	inline void VertexBufferLayout::Push<unsigned int>(unsigned int element_size) {
		m_LayoutElement.push_back({ element_size, GL_UNSIGNED_INT, GL_FALSE });
		m_StrideCount += VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT) * element_size;
	}

	template<>
	inline void VertexBufferLayout::Push<unsigned char>(unsigned int element_size) {
		m_LayoutElement.push_back({ element_size, GL_UNSIGNED_BYTE, GL_TRUE });
		m_StrideCount += VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE) * element_size;
	}
}