#ifndef PADDLE_H
#define PADDLE_H

#include "../AnimatedSprite.h"

class Paddle : public AnimatedSprite
{
public:
	Paddle(SDL_Surface* surface, SDL_Renderer* renderer) : AnimatedSprite(surface, renderer)
	{
		setAffectedByCollision(false);
	}
public:
	int id;
};

#endif