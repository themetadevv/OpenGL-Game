#pragma once

#include "OpenGL_Core.h"

namespace OpenGL::Utils {
	inline static void UnPackBytesAlignment(int unpack_alignment_bytes) {
		int current_unpack_alignment = 0;
		GLCall(glGetIntegerv(GL_UNPACK_ALIGNMENT, &current_unpack_alignment));

		//Log("Old Unpack alignment : ", current_unpack_alignment);

		if (current_unpack_alignment == unpack_alignment_bytes)
			return;

		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment_bytes));
	}
}