#include "EntitySprite.h"

void EntitySprite::update()
{
	Sprite::update();
	updateMovement();
}

void EntitySprite::updateMovement()
{
	int newX = mBody->x + mSpeed->x;
	int newY = mBody->y + mSpeed->y;

	if (mRestriction.get())
	{
		if (newX < mRestriction->x || newX + mBody->w > mRestriction->z)
		{
			newX = mBody->x;
		}

		if (newY < mRestriction->o || newY + mBody->h > mRestriction->y)
		{
			newY = mBody->y;
		}
	}

	mBody->x = newX;
	mBody->y = newY;
}

std::shared_ptr<Vector2<int>> EntitySprite::getSpeed()
{
	return mSpeed;
}

void EntitySprite::setSpeed(int x, int y)
{
	mSpeed->x = x;
	mSpeed->y = y;
}

void EntitySprite::modSpeed(int x, int y)
{
	mSpeed->x -= x;
	mSpeed->y -= y;
}

void EntitySprite::setMovementRestriction(std::shared_ptr<Vector4<int>> restriction)
{
	mRestriction = restriction;
}
