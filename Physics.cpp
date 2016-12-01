#include "Physics.h"
#include "SurfaceHelper.h"

namespace Physics
{
	bool isRectangularCollision(SDL_Rect* rect1, SDL_Rect* rect2)
	{
		SDL_Rect rect3;
		bool collision = SDL_IntersectRect(rect1, rect2, &rect3);
		return collision;
	}

	bool isRectangularCollision(Sprite* sprite, Sprite* sprite2)
	{
		SDL_Rect rect;
		rect.x = sprite->getBody()->x;
		rect.y = sprite->getBody()->y;
		rect.w = sprite->getBody()->w;
		rect.h = sprite->getBody()->h;

		SDL_Rect rect2;
		rect2.x = sprite2->getBody()->x;
		rect2.y = sprite2->getBody()->y;
		rect2.w = sprite2->getBody()->w;
		rect2.h = sprite2->getBody()->h;

		return isRectangularCollision(&rect, &rect2);
	}

	bool isRectangularPixelCollision(Sprite* sprite, Sprite* sprite2)
	{
		SDL_Rect rect;
		rect.x = sprite->getBody()->x;
		rect.y = sprite->getBody()->y;
		rect.w = sprite->getBody()->w;
		rect.h = sprite->getBody()->h;

		SDL_Rect rect2;
		rect2.x = sprite2->getBody()->x;
		rect2.y = sprite2->getBody()->y;
		rect2.w = sprite2->getBody()->w;
		rect2.h = sprite2->getBody()->h;

		SDL_Rect intersectRect;
		bool collision = SDL_IntersectRect(&rect, &rect2, &intersectRect);
		if (!collision) return false;

		for (int y = 0; y < intersectRect.h; y++)
			for (int x = 0; x < intersectRect.w; x++)
				if (!SurfaceHelper::isTransparent(sprite->getSurface(), x, y) && !SurfaceHelper::isTransparent(sprite2->getSurface(), x, y))
					return true;

		return false;
	}
}