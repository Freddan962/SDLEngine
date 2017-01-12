#include "Ball.h"
#include "Paddle.h"
#include <iostream>

Ball::Ball(SDL_Surface* surface, SDL_Renderer* renderer)
: AnimatedSprite(surface, renderer)
{
	collisionCheckTimer.setTime(1000);
	collisionCheckTimer.start();
}

void Ball::onCollide(Sprite* sprite)
{
	if (Paddle* pad = dynamic_cast<Paddle*>(sprite))
	{
		if (collisionCheckTimer.isReady())
		{
			invertHorizontalSpeed();
			collisionCheckTimer.reset();
		}
	}
}

void Ball::onLeftRestriction()
{
	invertHorizontalSpeed();
}

void Ball::onRightRestriction()
{
	invertHorizontalSpeed();
}

void Ball::onTopRestriction()
{
	invertVerticalSpeed();
}

void Ball::onBottomRestriction()
{
	invertVerticalSpeed();
}

void Ball::invertHorizontalSpeed()
{
	setSpeed(getSpeed().x*(-1), getSpeed().y);
}

void Ball::invertVerticalSpeed()
{
	setSpeed(getSpeed().x, getSpeed().y*(-1));
}

void Ball::update()
{
	AnimatedSprite::update();
}