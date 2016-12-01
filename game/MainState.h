#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "SDL.h"

#include <iostream>
#include "../State.h"
#include "../EntitySprite.h"
#include "../InputField.h"
#include "../AnimatedSprite.h"

class MainState : public State
{
public:
	MainState(Engine* engine)
		: State(engine, "MainState") 
	{
		mStaticAnimatedFrame = 0;
	}
	
	void update();
	void handleEvent(SDL_Event* event);
	void render();
	void staticButtonClick();

private:
	void load();
	void unload();

private:
	std::shared_ptr<EntitySprite> box1;
	std::shared_ptr<EntitySprite> box2;
	std::shared_ptr<Text> collisionText;
	std::shared_ptr<AnimatedSprite> mStaticAnimated;
	int mStaticAnimatedFrame;
};

#endif