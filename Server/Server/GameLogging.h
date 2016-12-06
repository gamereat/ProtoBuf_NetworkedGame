#pragma once
#include <iostream>

/**
Log game events into the console window
*/
class GameLogging
{
public:
	GameLogging();
	~GameLogging();

	/*
	STATIC 
	Log a normal message into console only viewable in debug mode

	@param output	string to be dispalyed in console 
	*/
	static void Log(std::string output);

	/*
	STATIC
	Log a Error message into console viable in all modes and coverd in red

	@param output	string to be dispalyed in console
	*/
	static void LogError(std::string output);

	/*
	STATIC
	Log a warning  message into console only viewable in all  modes

	@param output	string to be dispalyed in console
	*/
	static void LogWarning(char* output);


};

