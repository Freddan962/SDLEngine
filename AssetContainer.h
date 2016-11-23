#ifndef ASSETCONTAINER_H
#define ASSETCONTAINER_H

#include "SDL.h"
#include <map>

class AssetContainer
{
public:
	void addTexture(std::string, SDL_Texture* texture);
	SDL_Texture* getTexture(std::string name);

private:
	std::map<std::string, SDL_Texture*> mTextures;
};

#endif