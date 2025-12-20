
#include "pch.h"
#include "Core/Core.h"
#include "Core/Console.h"

#include "Utils.h"

namespace Core::Utils {
	const char* get_file_name_by_path(const char* path) {
		const char* file = path;
		for (const char* p = path; *p; ++p) {
			if (*p == '/' || *p == '\\')
				file = p + 1;
		}
		return file;
	}

	std::string to_lower(RoString v) {
		std::string tmp_string(v);

		for (auto& c : tmp_string)
			c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

		return tmp_string;
	}

}
