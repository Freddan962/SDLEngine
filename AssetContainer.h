#ifndef ASSETCONTAINER_H
#define ASSETCONTAINER_H

#include "SDL.h"
#include "sdl\include\SDL_mixer.h"
#include <map>

class AssetContainer
{
public:
	~AssetContainer();

	void addTexture(std::string, SDL_Texture* texture);
	SDL_Texture* getTexture(std::string name);

	void addChunk(std::string, Mix_Chunk* chunk);
	Mix_Chunk* getChunk(std::string name);

private:
	void freeChunks();

private:
	std::map<std::string, SDL_Texture*> mTextures;
	std::map<std::string, Mix_Chunk*> mChunks;
};

#endif