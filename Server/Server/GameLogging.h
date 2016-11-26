#pragma once
#include <iostream>

static class GameLogging
{
public:
	GameLogging();
	~GameLogging();

	static void Log(std::string output);

	static void LogError(std::string output); 

	static void LogWarning(char* output);


};

