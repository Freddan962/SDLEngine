#ifndef STATE_H
#define STATE_H

#include "SDL.h"

#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "HookContainer.h"

class Engine;
class AssetContainer;
class Sprite;

class State
{
public:
	State(Engine* engine, std::string name);

	virtual void update();
	virtual void handleEvent(SDL_Event* event);
	virtual void render();

	void addSprite(std::shared_ptr<Sprite> sprite);

private:
	virtual void load();
	virtual void unload();

	void updateSprites();
	void renderSprites();
	void checkForCollisions();

protected:
	Engine* mEngine;
	std::shared_ptr<AssetContainer> mAssets;
	HookContainer<SDL_Keycode> mKeyHooks;
	HookContainer<SDL_EventType> mEventHooks;

private:
	std::string mName;
	std::vector<std::shared_ptr<Sprite>> mSprites;
};

#endif