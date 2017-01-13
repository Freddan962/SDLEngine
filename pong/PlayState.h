#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "Paddle.h"
#include "../State.h"
#include "Player.h"
#include "Ball.h"
#include "../Text.h"
#include "PowerupSpeed.h"
#include "PowerupWorth.h"
#include "../Timer.h"

class PlayState : public State
{
public:
	PlayState(Engine* engine);

	void update();
	void render();
	void handleEvent(SDL_Event* event);
	void load();
	void unload();

	void score(int player, std::shared_ptr<Ball> ball);

private:
	void loadAssets();
	void setUp();

private:
	void moveUpLeft();
	void moveDownLeft();
	void moveStopLeft();
	void moveUpRight();
	void moveDownRight();
	void moveStopRight();
	void startGame();
	
	void homeButtonClick();
	void resetButtonClick();

	void spawnBall();
	void updateScore();
	void updateScoreText();
	void reset();
	void spawnPowerup();

	std::shared_ptr<Ball> createBall();
	void createBallTemporary();
	void removeTemporaryBalls();
	std::shared_ptr<Powerup> createPowerupTemporary();
	void removeTemporaryPowerups();

	void debugModeToggle();

private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Ball> mBall;
	std::shared_ptr<Paddle> mPaddle1, mPaddle2;
	std::shared_ptr<Button> mHomeButton;
	std::shared_ptr<Button> mResetButton;
	std::shared_ptr<Text> mScoreTxt;
	std::vector<std::shared_ptr<Ball>> mBalls;
	Timer mPowerupSpawnTimer;
	bool mPaddle1Active = true;

	int player1Score, player2Score;
	int bouncesForBallSpawn;
};

#endif