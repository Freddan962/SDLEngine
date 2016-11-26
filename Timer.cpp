#include "Timer.h"

Timer::Timer()
{
	mTime = 0;
	mStartTime = -1;
}

Timer::Timer(Uint32 time)
{
	mTime = time;
	mStartTime = -1;
}

bool Timer::isReady()
{
	if (mStartTime == -1) return false;

	int diff = SDL_GetTicks() - mStartTime;
	if (diff > mTime)
	{
		reset();
		return true;
	}

	return false;
}

void Timer::reset()
{
	mStartTime = SDL_GetTicks();
}

void Timer::start()
{
	reset();
}

void Timer::stop()
{
	mStartTime = -1;
}

void Timer::setTime(Uint32 time)
{
	mTime = time;
}