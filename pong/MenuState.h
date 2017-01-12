#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../State.h"
#include "Player.h"

class MenuState : public State
{
public:
	MenuState(Engine* engine) : State(engine, "MenuState") {}

	void update();
	void render();
	void handleEvent(SDL_Event* event);
	void load();
	void unload();
	void setPlayButtonText(std::string newText);

private:
	void loadAssets();
	void setUp();
	void playButtonClick();
	void highScoreButtonClick();
	void exitButtonClick();

private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Button> mPlayButton;
};

#endif