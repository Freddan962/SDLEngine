#include "ImageLoader.h"
#include <fstream>
#include "SDL_image.h"

ImageLoader::ImageLoader(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

SDL_Texture* ImageLoader::loadBMP(std::string path)
{
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* ImageLoader::loadPNG(std::string path)
{
	return IMG_LoadTexture(mRenderer, path.c_str());
}