#include "engineTime.h"

engineTime::engineTime()
{
}

engineTime::~engineTime()
{
}

engineTime* engineTime::get()
{
	static engineTime _engineTime;
	return &_engineTime;
}

double engineTime::getDeltaTime()
{
	return deltaTime;
}

double engineTime::getRunningTime()
{
	return runningTime;
}

double engineTime::getRunningTimeAsMilliseconds()
{
	return runningTime * 1000;
}

void engineTime::logFrameStart()
{

	start = std::chrono::system_clock::now();
}

void engineTime::logFrameEnd()
{
	end = std::chrono::system_clock::now();
	if (!paused)
	{
		deltaTime = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) * .001;
		runningTime += deltaTime;
	}
	else
	{
		deltaTime = 0;
	}
}

void engineTime::togglePause()
{
	paused = !paused;
}