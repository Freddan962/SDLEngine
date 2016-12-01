#ifndef CENTERER_H
#define CENTERER_H

#include "SDL.h"
#include "Vector2.h"
#include "Vector4.h"

class Sprite;
class Text;

class Centerer
{
public:
	static void center(Sprite* sprite, Vector2<int> area);
	static void centerHorizontal(Sprite* sprite, int width);
	static void centerVertical(Sprite* sprite, int height);

	static void center(SDL_Rect* rect, Vector2<int> area);
	static void centerHorizontal(SDL_Rect* rect, int width);
	static void centerVertical(SDL_Rect* rect, int height);
};

#endif