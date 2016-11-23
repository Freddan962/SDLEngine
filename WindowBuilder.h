#ifndef WINDOWBUILDER_H
#define WINDOWBUILDER_H

#include "SDL.h"
#include <string>

class WindowBuilder
{
public:
	static SDL_Window* build(std::string title, int width, int height)
	{
		SDL_Window* win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_HIDDEN);
		return win;
	}
};

#endif
