#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class engineTime
{
public:
	static engineTime* get();
	double getDeltaTime();

private:
	engineTime();
	~engineTime();
	engineTime(engineTime const&) {}
	engineTime& operator=(engineTime const&) {}

	engineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0;

	void logFrameStart();
	void logFrameEnd();

	friend class window;
};