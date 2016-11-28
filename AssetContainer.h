#ifndef ASSETCONTAINER_H
#define ASSETCONTAINER_H

#include "SDL.h"
#include "sdl\include\SDL_mixer.h"
#include <map>
#include "Asset.h"

class AssetContainer
{
public:
	Asset<SDL_Texture*> textures;
	Asset<Mix_Chunk*> chunks;
	Asset<TTF_Font*> fonts;
};

#endif