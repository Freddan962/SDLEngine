#include "SpriteCenterer.h"

void SpriteCenterer::center(Sprite* sprite, Vector2<int> area)
{
	centerHorizontal(sprite, area.x);
	centerVertical(sprite, area.y);
}

void SpriteCenterer::centerHorizontal(Sprite* sprite, int width)
{
	int x = width / 2 - sprite->getBody()->w / 2;
	sprite->getBody()->x = x;
}

void SpriteCenterer::centerVertical(Sprite* sprite, int height)
{
	int y = height / 2 - sprite->getBody()->h / 2;
	sprite->getBody()->y = y;
}