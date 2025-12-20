
#include "pch.h"
#include "Console.h"

ConsoleTextStyle operator|(ConsoleTextStyle a, ConsoleTextStyle b) {
	return static_cast<ConsoleTextStyle>(
		static_cast<int>(a) | static_cast<int>(b)
		);
}

ConsoleTextStyle operator&(ConsoleTextStyle a, ConsoleTextStyle b) {
	return static_cast<ConsoleTextStyle>(
		static_cast<int>(a) & static_cast<int>(b)
		);
}

void SetConsoleStyle(ConsoleTextStyle style) {
	int st = static_cast<int>(style);
	std::string code = "\033[";

	if (st & static_cast<int>(ConsoleTextStyle::Black)) code += "30;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Red)) code += "31;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Green)) code += "32;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Yellow)) code += "33;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Blue)) code += "34;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Magenta)) code += "35;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Cyan)) code += "36;"; 
	if (st & static_cast<int>(ConsoleTextStyle::White)) code += "37;"; 

	// Styles
	if (st & static_cast<int>(ConsoleTextStyle::Bold))  code += "1;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Dim))  code += "2;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Underline)) code += "4;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Blink)) code += "5;"; 
	if (st & static_cast<int>(ConsoleTextStyle::Reverse)) code += "7;"; 

	if (!code.empty() && code.back() == ';') code.pop_back();
	code += "m";

	std::cout << code;
}

void ResetConsoleStyle() {
	std::cout << "\033[0m";
}