#ifndef SPRITECENTERER_H
#define SPRITECENTERER_H

#include "Sprite.h"
#include "Vector2.h"

class SpriteCenterer
{
public:
	static void center(Sprite* sprite, Vector2<int> area);
	static void centerHorizontal(Sprite* sprite, int width);
	static void centerVertical(Sprite* sprite, int height);
};

#endif