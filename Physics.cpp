#include "Physics.h"

namespace Physics
{
	bool isRectangularCollision(SDL_Rect* rect1, SDL_Rect* rect2)
	{
		SDL_Rect* rect3 = new SDL_Rect;
		SDL_bool intersect = SDL_IntersectRect(rect1, rect2, rect3);
		delete rect3;

		return intersect;
	}
}