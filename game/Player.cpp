#include "Player.h"
#include <iostream>
#include "Projectile.h"

Player::Player(SDL_Texture * texture)
	: EntitySprite(texture)
{
	mCurrSpeed.x = 4;
	mFireTimer.setTime(1000);
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

void Player::fire()
{
	if (mFireTimer.isReady())
		std::cout << "fire" << std::endl;
}
