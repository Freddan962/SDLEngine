#ifndef STATE_H
#define STATE_H

#include "SDL.h"

#include <iostream>
#include <vector>
#include <memory>
#include <map>

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
	void addHook(SDL_EventType type, void(*func)(SDL_EventType));

private:
	virtual void load();
	virtual void unload();

	void updateSprites();
	void renderSprites();
	void checkForCollisions();

protected:
	Engine* mEngine;
	std::shared_ptr<AssetContainer> mAssets;
	std::map<SDL_EventType, std::vector<void(*)(SDL_EventType)>> mHooks;

private:
	std::string mName;
	std::vector<std::shared_ptr<Sprite>> mSprites;
};

#endif