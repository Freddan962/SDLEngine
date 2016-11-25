#include "EntitySprite.h"

void EntitySprite::update()
{
	Sprite::update();

	mBody->x += (int)mSpeed->x;
	mBody->y += (int)mSpeed->y;
}

std::shared_ptr<Vector2<float>> EntitySprite::getSpeed()
{
	return mSpeed;
}

void EntitySprite::setSpeed(float x, float y)
{
	mSpeed->x = x;
	mSpeed->y = y;
}

void EntitySprite::modSpeed(float x, float y)
{
	mSpeed->x -= x;
	mSpeed->y -= y;
}
