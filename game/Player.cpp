#include "Player.h"
#include <iostream>
#include "Projectile.h"
#include "../SpriteCenterer.h"
#include "../Sound.h"

Player::Player(SDL_Texture * texture)
	: EntitySprite(texture)
{
	mCurrSpeed.x = 6;
	mProjectileSpeed.y = -8;
	mFireTimer.setTime(500);
	mFireTimer.start();
}

void Player::update()
{
	EntitySprite::update();
}

void Player::render(SDL_Renderer* renderer)
{
	EntitySprite::render(renderer);
}

void Player::moveLeft()
{
	setSpeed(mCurrSpeed.x * - 1, 0);
}

void Player::moveRight()
{
	setSpeed(mCurrSpeed.x, 0);
}

void Player::stopMoveHorizontal()
{
	setSpeed(0, getSpeed().y);
}

void Player::setProjectile(std::shared_ptr<Projectile> projectile)
{
	mProjectile = projectile;
}

void Player::setProjectileFiringSound(std::shared_ptr<Sound> sound)
{
	mProjectileFiringSound = sound;
}

std::shared_ptr<Projectile> Player::fire()
{
	Projectile projectile(*mProjectile.get());
	std::shared_ptr<Projectile> copy = std::make_shared<Projectile>(projectile);
	SpriteCenterer::centerHorizontal(copy.get(), getBody()->w);
	copy->getBody()->x += getBody()->x;
	copy->getBody()->y = getBody()->y - copy->getBody()->h;
	copy->setSpeed(0, mProjectileSpeed.y);

	mProjectileFiringSound->play();
	return copy;
}

bool Player::canFire() 
{
	if (!mProjectile.get()) return false;
	return mFireTimer.isReady();
}

Vector2<float> Player::getProjectileSpeed()
{
	return mProjectileSpeed;
}
