#ifndef STATE_H
#define STATE_H

#include "SDL.h"

#include <iostream>
#include <string>

class State
{
public:
	State(std::string name);

	virtual void update();
	virtual void handleEvent(SDL_Event* event);
	virtual void render();

private:
	std::string mName;
};

#endif