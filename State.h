#ifndef STATE_H
#define STATE_H

#include "SDL.h"

#include <iostream>
#include <vector>
#include <memory>

class Engine;
class AssetContainer;

class State
{
public:
	State(Engine* engine, std::string name);

	virtual void update();
	virtual void handleEvent(SDL_Event* event);
	virtual void render();

private:
	virtual void load();
	virtual void unload();

protected:
	Engine* mEngine;
	std::shared_ptr<AssetContainer> mAssets;

private:
	std::string mName;
};

#endif