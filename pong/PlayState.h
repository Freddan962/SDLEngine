#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "Paddle.h"
#include "../State.h"
#include "Player.h"
#include "Ball.h"

class PlayState : public State
{
public:
	PlayState(Engine* engine) : State(engine, "PlayState") {}

	void update();
	void render();
	void handleEvent(SDL_Event* event);
	void load();
	void unload();

private:
	void loadAssets();
	void setUp();

private:
	void moveUp();
	void moveDown();
	void moveStop();
	void startGame();

private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Paddle> mPaddle1, mPaddle2;
	std::shared_ptr<Ball> mBall;
	bool mPaddle1Active = true;
};

#endif