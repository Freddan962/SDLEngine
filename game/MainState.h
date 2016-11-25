#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "SDL.h"

#include <iostream>
#include "../State.h"
#include "../EntitySprite.h"
#include "../InputField.h"
#include "../Test.h"

class Test;

class MainState : public State
{
public:
	MainState(Engine* engine)
		: State(engine, "MainState"),
		mTest(new Test)
	{ load(); }
	
	void update();
	void handleEvent(SDL_Event* event);
	void render();

private:
	void load();
	void unload();

private:
	std::shared_ptr<EntitySprite> box1;
	std::shared_ptr<EntitySprite> box2;
	std::shared_ptr<Test> mTest;
};

#endif