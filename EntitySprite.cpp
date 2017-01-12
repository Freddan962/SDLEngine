#include "EntitySprite.h"

EntitySprite::EntitySprite(const EntitySprite& other)
	: Sprite(other)
{
	mSpeed = other.getSpeed();

	Vector4<int> oRestriction = other.getMovementRestriction();
	mRestriction.x = oRestriction.x;
	mRestriction.y = oRestriction.y;
	mRestriction.w = oRestriction.w;
	mRestriction.h = oRestriction.h;
}

EntitySprite* EntitySprite::getInstance(SDL_Surface* surface, SDL_Renderer* renderer)
{
	return new EntitySprite(surface, renderer);
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

	if (mRestriction.x != 0 || mRestriction.y != 0 || mRestriction.w != 0 || mRestriction.h != 0)
	{
		if (newX < mRestriction.x)
		{
			newX = mBody->x;
			onLeftRestriction();
		}

		if (newX + mBody->w > mRestriction.w)
		{
			newX = mBody->x;
			onRightRestriction();
		}
		
		if (newY < mRestriction.y)
		{
			newY = mBody->y;
			onTopRestriction();
		}

		if (newY + mBody->h > mRestriction.h)
		{
			newY = mBody->y;
			onBottomRestriction();
		}
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

void EntitySprite::setMovementRestriction(int x, int y, int w, int h)
{
	Vector4<int> restriction;
	restriction.x = x;
	restriction.y = y;
	restriction.w = w;
	restriction.h= h;
	mRestriction = restriction;
}

void EntitySprite::setMovementRestriction(Vector4<int> restriction)
{
	mRestriction = restriction;
}

Vector4<int> EntitySprite::getMovementRestriction() const
{
	return mRestriction;
}

