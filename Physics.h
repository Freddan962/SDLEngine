#ifndef PHYSICS_H
#define PHYSICS_H

#include "SDL.h"

namespace Physics
{
	bool isRectangularCollision(SDL_Rect* rect1, SDL_Rect* rect2);
}

#endif