#include "Player.h"
#include <iostream>

Player::Player(SDL_Texture * texture)
	: EntitySprite(texture)
{
	mCurrSpeed.x = 2;
}

void Player::update()
{
	EntitySprite::update();
}

void Player::moveLeft()
{
	setSpeed(mCurrSpeed.x * - 1, 0);
}

void Player::moveRight()
{
	setSpeed(mCurrSpeed.x, 0);
}
