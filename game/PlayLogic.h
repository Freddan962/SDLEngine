#ifndef PLAYLOGIC_H
#define PLAYLOGIC_H

#include "SDL.h"
#include <vector>
#include "Projectile.h"

class State;

class PlayLogic
{
public:
	PlayLogic(State* state);

	void update();
	void render(SDL_Renderer* renderer);

	void playerShoot();

private:
	State* mState;
};

#endif