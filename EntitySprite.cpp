#include "EntitySprite.h"

EntitySprite::EntitySprite(const EntitySprite& other)
	: Sprite(other)
{
	mSpeed = other.getSpeed();

	std::shared_ptr<Vector4<int>> oRestriction = other.getMovementRestriction();
	if (oRestriction)
	{
		mRestriction->x = oRestriction->x;
		mRestriction->y = oRestriction->y;
		mRestriction->z = oRestriction->z;
		mRestriction->o = oRestriction->o;
	}
}

void EntitySprite::update()
{
	Sprite::update();
	updateMovement();
}

void EntitySprite::updateMovement()
{
	int newX = mBody->x + mSpeed.x;
	int newY = mBody->y + mSpeed.y;

	if (mRestriction.get())
	{
		if (newX < mRestriction->x || newX + mBody->w > mRestriction->z)
			newX = mBody->x;

		if (newY < mRestriction->o || newY + mBody->h > mRestriction->y)
			newY = mBody->y;
	}

	mBody->x = newX;
	mBody->y = newY;
}

Vector2<int> EntitySprite::getSpeed() const
{
	return mSpeed;
}

void EntitySprite::setSpeed(int x, int y)
{
	mSpeed.x = x;
	mSpeed.y = y;
}

void EntitySprite::modSpeed(int x, int y)
{
	mSpeed.x -= x;
	mSpeed.y -= y;
}

void EntitySprite::setMovementRestriction(std::shared_ptr<Vector4<int>> restriction)
{
	mRestriction = restriction;
}

std::shared_ptr<Vector4<int>> EntitySprite::getMovementRestriction() const
{
	return mRestriction;
}
