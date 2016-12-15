#ifndef PADDLE_H
#define PADDLE_H

#include "../EntitySprite.h"

class Paddle : public EntitySprite
{
public:
	Paddle(SDL_Surface* surface, SDL_Renderer* renderer) : EntitySprite(surface, renderer) {}

public:
	int id;

};

#endif