#include "ImageLoader.h"
#include <fstream>

ImageLoader::ImageLoader(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

SDL_Texture* ImageLoader::loadBMP(std::string path)
{

	std::ifstream infile(path);
	bool good = infile.good();

	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}