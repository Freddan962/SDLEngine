#ifndef WELCOMESTATE_H
#define WELCOMESTATE_H

#include "../State.h"

class WelcomeState : public State
{
public:
	WelcomeState(Engine* engine) : State(engine, "WelcomeState") {}

	void update();
	void render();
	void handleEvent(SDL_Event* event);
	void load();
	void unload();

private:
	void loadAssets();
	void setUp();
};

#endif