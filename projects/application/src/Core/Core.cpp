
#include "pch.h"
#include "Core.h"
#include "Console.h"

const char* GetFileName(const char* path) {
	const char* file = path;
	for (const char* p = path; *p; ++p) {
		if (*p == '/' || *p == '\\')
			file = p + 1;
	}
	return file;
}

bool CoreCheckError(
	bool condition,
	RoString error_msg,
	const char* condition_name,
	const char* file,
	int line
)

{
	if (condition)
		return true;

	ResetConsoleStyle();
	SetConsoleStyle(ConsoleTextStyle::Cyan);
	std::cout << "\n<--- " << "ASSERT" << " ----------------------------->\n";

	SetConsoleStyle(ConsoleTextStyle::White);
	std::cout << "| Condition : ";

	SetConsoleStyle(ConsoleTextStyle::Green);
	std::cout << condition_name << "\n";

	SetConsoleStyle(ConsoleTextStyle::White);
	std::cout << "| Location  : ";

	SetConsoleStyle(ConsoleTextStyle::Blue | ConsoleTextStyle::Bold);
	std::cout << GetFileName(file) << ":" << line << "\n";

	SetConsoleStyle(ConsoleTextStyle::White);
	std::cout << "| Message   : ";

	SetConsoleStyle(ConsoleTextStyle::Yellow);
	std::cout << error_msg << "\n";

	SetConsoleStyle(ConsoleTextStyle::Cyan);
	std::cout << "<--------------------------------------------------->\n";

	return false;
}
