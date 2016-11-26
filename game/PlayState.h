#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "../State.h"
#include "PlayLogic.h"

class Engine;
class Player;

class PlayState : public State
{
public:
	PlayState(Engine* engine);

	void update();
	void render();
	void handleEvent(SDL_Event* event);

private:
	void load();
	void unload();

	void loadAssets();
	void prepareEntities();
	void bindHooks();

private:

private:
	std::shared_ptr<Player> mPlayer;
	PlayLogic mPlayLogic;
};

#endif