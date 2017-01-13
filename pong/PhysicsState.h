#ifndef PHYSICSSTATE_H
#define PHYSICSSTATE_H

#include "../State.h"

class PhysicsState : public State
{
public:
	PhysicsState(Engine* engine);

	void update();
	void render();
	void handleEvent(SDL_Event* event);
	void load();
	void unload();

	void reset();
	void start();

	void returnButtonClick();
	void resetButtonClick();

private:
	void loadAssets();
	void setUp();

private:
	void debugModeToggle();

private:
};

#endif