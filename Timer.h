#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

class Timer
{
public:
	Timer();
	Timer(Uint32 time);

	bool isReady();
	void reset();
	void start();
	void stop();
	void setTime(Uint32 time);
	void forceReady();

private:
	int mStartTime;
	Uint32 mTime;
	bool mForceReady;
};

#endif