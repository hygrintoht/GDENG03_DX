#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class engineTime
{
public:
	static engineTime* get();
	double getDeltaTime();
	double getRunningTime();
	double getRunningTimeAsMilliseconds();
	void togglePause();

private:
	engineTime();
	~engineTime();
	engineTime(engineTime const&) {}
	engineTime& operator=(engineTime const&) {}

	engineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0;

	double runningTime = 0;

	bool paused = false;

	void logFrameStart();
	void logFrameEnd();

	friend class window;
};