#include "Ball.h"
#include "Paddle.h"
#include <iostream>

void Ball::onCollide(Sprite* sprite)
{
	if (Paddle* pad = dynamic_cast<Paddle*>(sprite))
	{
		if (pad->id == 1)
		{
			setSpeed(getSpeed().x*(-1), getSpeed().y);
			getBody()->x = pad->getBody()->x + pad->getBody()->w + getSpeed().x;
			std::cout << " " << std::endl;
			setSpeed(0, 0);
			pad->setSpeed(0, 0);
		}
		else if (pad->id == 2)
		{
			setSpeed(getSpeed().x*(-1), getSpeed().y);
			std::cout << " " << std::endl;
		}
	}
}
void Ball::onLeftRestriction()
{
	setSpeed(getSpeed().x*(-1), getSpeed().y);
}
void Ball::onRightRestriction()
{
	setSpeed(getSpeed().x*(-1), getSpeed().y);
}
void Ball::onTopRestriction()
{
	setSpeed(getSpeed().x, getSpeed().y*(-1));
}
void Ball::onBottomRestriction()
{
	setSpeed(getSpeed().x, getSpeed().y*(-1));
}