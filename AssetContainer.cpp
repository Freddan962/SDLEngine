#include "AssetContainer.h"
#include <iostream>
#include <string>
#include <map>

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