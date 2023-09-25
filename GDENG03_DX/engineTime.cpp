#include "engineTime.h"

/*
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();
*/

void engineTime::init()
{
	if (sharedInstance == nullptr)
		sharedInstance = new engineTime();
}

double engineTime::getDeltaTime()
{
	return deltaTime;
}

void engineTime::logFrameStart()
{
	start = std::chrono::high_resolution_clock::now();
}
