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

void engineTime::logFrameStart()
{

	start = std::chrono::system_clock::now();
}

void engineTime::logFrameEnd()
{
	end = std::chrono::system_clock::now();
	deltaTime = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) * .001;
}