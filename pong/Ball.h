#ifndef BALL_H
#define BALL_H

#include "../AnimatedSprite.h"
#include "../Timer.h"

class Ball : public AnimatedSprite
{
public:
	Ball(SDL_Surface* surface, SDL_Renderer* renderer);
	
	void onCollide(Sprite* sprite);
	void onLeftRestriction();
	void onRightRestriction();
	void onTopRestriction();
	void onBottomRestriction();

	void update();
	void launch();

	int getBounces();
	void setBounces(int bounces);
	Vector2<int> getMaxSpeed();

	void setScoreWorth(int worth);
	int getScoreWorth();

private:
	void invertHorizontalSpeed();
	void invertVerticalSpeed();

public:
	bool reachedLeft, reachedRight;
	bool shouldDelete;

private:
	Vector2<int> mSpeed;
	Timer collisionCheckTimer;
	int mBounces;
	int mScoreWorth;
	unsigned char mEffectFlag;
};

#endif