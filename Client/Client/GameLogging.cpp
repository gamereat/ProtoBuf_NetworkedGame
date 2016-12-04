#include "GameLogging.h"
#include <Windows.h>


GameLogging::GameLogging()
{
}


GameLogging::~GameLogging()
{
}

void GameLogging::Log(std::string output)
{
	// Set the colour of the message
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
	// only log information if in debug mode
#ifndef DEBUG
//	std::cout << output.c_str() << '\n';
#endif // !DEBUG

}

void GameLogging::LogError(std::string output)
{
	// Set the colour of the message

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
	std::cout << "ERROR -";
 
	std::cout << output.c_str() << '\n';
}

void GameLogging::LogWarning(char* output)
{

	// Set the colour of the message

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
	std::cout << "WARNING -";

	std::cout << output << '\n';
}
