#ifndef PHYSICS_H
#define PHYSICS_H

#include "SDL.h"
#include "Sprite.h"

namespace Physics
{
	bool isRectangularCollision(SDL_Rect* rect1, SDL_Rect* rect2);
	bool isRectangularCollision(Sprite* sprite, Sprite* sprite2);
	bool isRectangularPixelCollision(Sprite* sprite, Sprite* sprite2);
}

#endif