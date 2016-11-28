#include "AssetLoader.h"
#include <fstream>
#include <SDL_image.h>

AssetLoader::AssetLoader(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

SDL_Texture* AssetLoader::loadBMP(std::string path)
{
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* AssetLoader::loadPNG(std::string path)
{
	return IMG_LoadTexture(mRenderer, path.c_str());
}

Mix_Chunk* AssetLoader::loadWAV(std::string path)
{
	return Mix_LoadWAV(path.c_str());
}

Mix_Chunk* AssetLoader::loadOGG(std::string path)
{
	return loadWAV(path);
}

TTF_Font* AssetLoader::loadFont(std::string path, int size)
{
	return TTF_OpenFont(path.c_str(), size);
}

