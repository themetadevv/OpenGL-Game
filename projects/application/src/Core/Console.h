#pragma once

enum class ConsoleTextStyle : int {
	None = 0,

	// colors
	Black = 1 << 0,
	Red = 1 << 1,
	Green = 1 << 2,
	Yellow = 1 << 3,
	Blue = 1 << 4,
	Magenta = 1 << 5,
	Cyan = 1 << 6,
	White = 1 << 7,

	// styles
	Bold = 1 << 8,
	Dim = 1 << 9,
	Underline = 1 << 10,
	Blink = 1 << 11,
	Reverse = 1 << 12
};

ConsoleTextStyle operator|(ConsoleTextStyle a, ConsoleTextStyle b);
ConsoleTextStyle operator&(ConsoleTextStyle a, ConsoleTextStyle b);

void SetConsoleStyle(ConsoleTextStyle c);
void ResetConsoleStyle();