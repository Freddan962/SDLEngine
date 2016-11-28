#include "SoundLoader.h"

Mix_Chunk* SoundLoader::loadWAV(std::string file)
{
	return Mix_LoadWAV(file.c_str());
}

Mix_Chunk* SoundLoader::loadOGG(std::string file)
{
	return loadWAV(file);
}