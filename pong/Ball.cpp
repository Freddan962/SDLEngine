#include "Ball.h"
#include "Paddle.h"
#include <iostream>
#include <random>

Ball::Ball(SDL_Surface* surface, SDL_Renderer* renderer)
	: AnimatedSprite(surface, renderer),
	reachedLeft(false),
	reachedRight(false),
	shouldDelete(false),
	mBounces(0),
	mScoreWorth(1),
	mEffectFlag(0)
{
	collisionCheckTimer.setTime(1000);
	collisionCheckTimer.start();

	mSpeed.x = 8;
	mSpeed.y = 8;
}

void Ball::onCollide(Sprite* sprite)
{
	EntitySprite::onCollide(sprite);
	if (!sprite->isCollidable()) return;

	if (Paddle* pad = dynamic_cast<Paddle*>(sprite))
	{
		invertVerticalSpeed();
		mBounces++;
	}
}

void Ball::onLeftRestriction()
{
	reachedLeft = true;
	invertHorizontalSpeed();
	setVelocity(getVelocity().x * getElasticity(), getVelocity().y);
}

void Ball::onRightRestriction()
{
	reachedRight = true;
	invertHorizontalSpeed();
	setVelocity(getVelocity().x * getElasticity(), getVelocity().y);
}

void Ball::onTopRestriction()
{
	invertVerticalSpeed();
	setVelocity(getVelocity().x, getVelocity().y * getElasticity());
}

void Ball::onBottomRestriction()
{
	invertVerticalSpeed();
	setVelocity(getVelocity().x, getVelocity().y * getElasticity());
}

void Ball::invertHorizontalSpeed()
{
	setVelocity(getVelocity().x*(-1), getVelocity().y);
}

void Ball::invertVerticalSpeed()
{
	setVelocity(getVelocity().x, getVelocity().y*(-1));
}

void Ball::update()
{
	AnimatedSprite::update();
}

void Ball::launch()
{	
	int xSpeed = 0;
	int ySpeed = 0;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1, 3);

	while (xSpeed == 0 || ySpeed == 0)
	{
		int dir = dist(mt);
		if (dir == 1)
			xSpeed = mSpeed.x * -1;
		else
			xSpeed = mSpeed.x;

		std::random_device rd2;
		std::mt19937 mt2(rd2());
		std::uniform_real_distribution<double> dist2(mSpeed.y * -1, mSpeed.y);
		ySpeed = dist2(mt2);
	}

	setVelocity(xSpeed, ySpeed);
}

int Ball::getBounces() { return mBounces; }
void Ball::setBounces(int bounces) { mBounces = bounces; }
Vector2<int> Ball::getMaxSpeed() { return mSpeed; }
void Ball::setScoreWorth(int worth) { mScoreWorth = worth; }
int Ball::getScoreWorth() { return mScoreWorth; }