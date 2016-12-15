#include "Ball.h"
#include "Paddle.h"
#include <iostream>

void Ball::onCollide(Sprite* sprite)
{
	if (Paddle* pad = dynamic_cast<Paddle*>(sprite))
	{
		if (pad->id == 1)
		{
			invertHorizontalSpeed();
			getBody()->x = pad->getBody()->x + pad->getBody()->w - getSpeed().x + 1;
		}
		else if (pad->id == 2)
		{
			invertHorizontalSpeed();
			getBody()->x = pad->getBody()->x - 1 - getBody()->w;
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