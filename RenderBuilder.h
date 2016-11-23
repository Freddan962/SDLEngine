#ifndef RENDERBUILDER_H
#define RENDERBUILDER_H

#include "SDL.h"

class RenderBuilder
{
public:
	static SDL_Renderer* build(SDL_Window* window)
	{
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		return renderer;
	}
};

#endif