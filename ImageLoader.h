#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "SDL.h"
#include <string>

class Engine;

class ImageLoader
{
public:

	ImageLoader(SDL_Renderer* renderer);
	SDL_Texture* loadBMP(std::string path);

private:
	SDL_Renderer* mRenderer;
};

#endif