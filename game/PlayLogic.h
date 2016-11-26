#ifndef PLAYLOGIC_H
#define PLAYLOGIC_H

#include "SDL.h"

class State;

class PlayLogic
{
public:
	PlayLogic(State* state);

	void update();
	void render(SDL_Renderer* renderer);

private:
	void playerShoot();

private:
	State* mState;
};

#endif