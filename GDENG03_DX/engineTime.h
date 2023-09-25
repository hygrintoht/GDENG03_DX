#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class engineTime
{
public:
	static void init();
	static double getDeltaTime();

private:
	engineTime();
	~engineTime();
	engineTime(engineTime const&) {};
	engineTime& operator=(engineTime const&) {};

	static engineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0f;

	static void logFrameStart();
	static void logFrameEnd();

	friend class Window;
};