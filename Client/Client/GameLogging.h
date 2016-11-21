#pragma once
#include <iostream>

static class GameLogging
{
public:
	GameLogging();
	~GameLogging();

	static void Log(char*);

	static void LogError(char* output);

	static void LogWarning(char* output);


};

