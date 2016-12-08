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
	AssetLoader(SDL_Renderer*, std::string assetPath);

	SDL_Surface* loadBMP(std::string path);
	SDL_Surface* loadPNG(std::string path);
	Mix_Chunk* loadWAV(std::string path);
	Mix_Chunk* loadOGG(std::string path);
	TTF_Font* loadFont(std::string path, int size);

	void setAssetPath(std::string);
	std::string getAssetPath();

private:
	SDL_Renderer* mRenderer;
	std::string mAssetPath;
};

#endif