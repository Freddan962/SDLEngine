#include "AssetLoader.h"
#include <fstream>
#include <SDL_image.h>

AssetLoader::AssetLoader(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

AssetLoader::AssetLoader(SDL_Renderer* renderer, std::string assetPath)
{
	mRenderer = renderer;
	mAssetPath = assetPath;
}

SDL_Surface* AssetLoader::loadBMP(std::string path)
{
	return SDL_LoadBMP((mAssetPath + path).c_str());
}

SDL_Surface* AssetLoader::loadPNG(std::string path)
{
	return IMG_Load((mAssetPath + path).c_str());
}

Mix_Chunk* AssetLoader::loadWAV(std::string path)
{
	return Mix_LoadWAV((mAssetPath + path).c_str());
}

Mix_Chunk* AssetLoader::loadOGG(std::string path)
{
	return loadWAV((mAssetPath + path).c_str());
}

TTF_Font* AssetLoader::loadFont(std::string path, int size)
{
	return TTF_OpenFont((mAssetPath + path).c_str(), size);
}

void AssetLoader::setAssetPath(std::string assetPath)
{
	mAssetPath = assetPath;
}

std::string AssetLoader::getAssetPath()
{
	return mAssetPath;
}


