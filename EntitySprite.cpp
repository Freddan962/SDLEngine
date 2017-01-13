#include "EntitySprite.h"
#include <iostream>

EntitySprite::EntitySprite(const EntitySprite& other)
	: Sprite(other),
	mAffectedByGravity(false),
	mElasticity(1),
	mCollisionSinceLastFrame(false)
{
	mVelocity = other.getVelocity();

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
	updateGravity();
}

void EntitySprite::onCollide(Sprite* sprite)
{
	EntitySprite* eSprite = dynamic_cast<EntitySprite*>(sprite);

	if (eSprite && eSprite->isCollidable())
	{
		Sprite::onCollide(sprite);
		if (!affectedByCollision()) return;

		Vector2<int> dCoordinates;
		dCoordinates.x = getCenter().x - eSprite->getCenter().x;
		dCoordinates.y = getCenter().y - eSprite->getCenter().y;

		bool collisionLeft(false), collisionRight(false), collisionTop(false), collisionBottom(false);

		if (dCoordinates.x != 0) //No horizontal collision
		{
			if (dCoordinates.x < 0) //Collision on left side
				collisionLeft = true;
			else
				collisionRight = true;
		}

		if (dCoordinates.y != 0) //No vertical collision
		{
			if (dCoordinates.y < 0) //Collision on top side
				collisionTop = true;
			else
				collisionBottom = true;
		}

		if (collisionTop || collisionBottom)
			setVelocity(getVelocity().x, getVelocity().y * -1);

		if (collisionLeft || collisionRight)
			setVelocity(getVelocity().x * -1, getVelocity().y);

		updateMovement();
	}
}

void EntitySprite::updateMovement()
{
	updateMovement(mVelocity.x, mVelocity.y);

	if (mCollisionSinceLastFrame)
	{
		mVelocity.x *= mElasticity;
		mVelocity.y *= mElasticity;
		mCollisionSinceLastFrame = false;
	}
}

void EntitySprite::updateMovement(double modX, double modY)
{
	int newX = mBody->x + modX;
	int newY = mBody->y + modY;

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

bool EntitySprite::isMoving()
{
	if (getVelocity().x != 0)
		return true;

	if (getVelocity().y != 0)
		return true;
}

double EntitySprite::getElasticity()
{
	return mElasticity;
}

void EntitySprite::setElasticity(double elasticity)
{
	mElasticity = elasticity;
}

void EntitySprite::setVelocity(double x, double y)
{
	mVelocity.x = x;
	mVelocity.y = y;
}

void EntitySprite::modVelocity(double x, double y)
{
	mVelocity.x += x;
	mVelocity.y += y;
}

Vector2<double> EntitySprite::getVelocity() const
{
	return mVelocity;
}

bool EntitySprite::affectedByGravity()
{
	return mAffectedByGravity;
}

void EntitySprite::setAffectedByGravity(bool affected)
{
	mAffectedByGravity = affected;
}

void EntitySprite::updateGravity()
{
	if (affectedByGravity())
		mVelocity.y += (double)2 / 60;
}

bool EntitySprite::affectedByCollision()
{
	return mAffectedByCollision;
}

void EntitySprite::setAffectedByCollision(bool affected)
{
	mAffectedByCollision = affected;
}