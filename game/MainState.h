#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "SDL.h"

#include <iostream>
#include "../State.h"

class MainState : public State
{
public:
	MainState() : State("MainState") { load(); }

	void update();
	void handleEvent(SDL_Event* event);
	void render();

private:
	void load();
	void unload();
};

#endif