#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>

class AssetLoader
{
public:
	AssetLoader(SDL_Renderer* renderer);

	SDL_Texture* loadBMP(std::string path);
	SDL_Texture* loadPNG(std::string path);

	Mix_Chunk* loadWAV(std::string path);
	Mix_Chunk* loadOGG(std::string path);

	TTF_Font* loadFont(std::string path, int size);

private:
	SDL_Renderer* mRenderer;
};

#endif