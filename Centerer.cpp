#include "Centerer.h"
#include "Sprite.h"

void Centerer::center(Sprite* sprite, Vector2<int> area)
{
	centerHorizontal(sprite, area.x);
	centerVertical(sprite, area.y);
}

void Centerer::centerHorizontal(Sprite* sprite, int width)
{
	int x = width / 2 - sprite->getBody()->w / 2;
	sprite->getBody()->x = x;
}

void Centerer::centerVertical(Sprite* sprite, int height)
{
	int y = height / 2 - sprite->getBody()->h / 2;
	sprite->getBody()->y = y;
}

void Centerer::center(SDL_Rect* rect, Vector2<int> area)
{
	centerHorizontal(rect, area.x);
	centerVertical(rect, area.y);
}

void Centerer::centerHorizontal(SDL_Rect* rect, int width)
{

}

void Centerer::centerVertical(SDL_Rect* rect, int height)
{

}