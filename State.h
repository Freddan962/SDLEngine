#ifndef STATE_H
#define STATE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "HookContainer.h"
#include "GUI.h"
#include "MapVector.h"

class Engine;
class AssetContainer;
class Sprite;
class Sound;

class State
{
public:
	State(Engine* engine, std::string name);

	virtual void update();
	virtual void handleEvent(SDL_Event* event);
	virtual void render();
	virtual void load();
	virtual void unload();

private:
	void updateSprites();
	void renderSprites();
	void checkForCollisions();
	void pauseAllSounds();

public:
	MapVector <std::shared_ptr<Sprite>> sprites;
	MapVector <std::shared_ptr<Sound>> sounds;
	MapVector <std::shared_ptr<TTF_Font>> fonts;
	MapVector <std::shared_ptr<Sprite>> savedSprites;

protected:
	Engine* mEngine;
	std::shared_ptr<AssetContainer> mAssets;
	HookContainer<SDL_Keycode> mKeyHooks;
	HookContainer<SDL_EventType> mEventHooks;
	GUI::GUI mGUI;

private:
	std::string mName;
};

#endif