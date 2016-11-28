#include "AssetContainer.h"
#include <iostream>
#include <string>
#include <map>

AssetContainer::~AssetContainer()
{
	freeChunks();
}

void AssetContainer::addTexture(std::string key, SDL_Texture* texture)
{
	if (mTextures.find(key) != mTextures.end())
	{
		std::cout << "Error: Texture with key [" << key << "] already exists!" << std::endl;
		return;
	}

	mTextures.insert(std::pair<std::string, SDL_Texture*>(key, texture));
}

SDL_Texture* AssetContainer::getTexture(std::string name)
{
	auto pos = mTextures.find(name);

	if (pos == mTextures.end())
		return nullptr;
	else
		return pos->second;
}

void AssetContainer::addChunk(std::string key, Mix_Chunk* chunk)
{
	if (mChunks.find(key) != mChunks.end())
	{
		std::cout << "Error: Texture with key [" << key << "] already exists!" << std::endl;
		return;
	}

	mChunks.insert(std::pair<std::string, Mix_Chunk*>(key, chunk));
}

Mix_Chunk* AssetContainer::getChunk(std::string name)
{
	auto pos = mChunks.find(name);

	if (pos == mChunks.end())
		return nullptr;
	else
		return pos->second;
}

void AssetContainer::freeChunks()
{
	for (std::map<std::string, Mix_Chunk*>::iterator it = mChunks.begin(); it != mChunks.end(); it++)
		Mix_FreeChunk(it->second);
}