#ifndef STATE_H
#define STATE_H

#include "SDL.h"

#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "HookContainer.h"
#include "GUI.h"

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

	void addSprite(std::string, std::shared_ptr<Sprite> sprite);
	std::vector<std::shared_ptr<Sprite>>* getSprites(std::string name);

private:
	virtual void load();
	virtual void unload();

	void updateSprites();
	void renderSprites();
	void checkForCollisions();

	std::vector<std::shared_ptr<Sprite>> getSprites();

protected:
	Engine* mEngine;
	std::shared_ptr<AssetContainer> mAssets;
	HookContainer<SDL_Keycode> mKeyHooks;
	HookContainer<SDL_EventType> mEventHooks;
	GUI::GUI mGUI;

private:
	std::string mName;
	std::map<std::string, std::vector<std::shared_ptr<Sprite>>> mSprites;
};

#endif