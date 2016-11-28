#ifndef SOUNDLOADER_H
#define SOUNDLOADER_H

#include <string>
#include <SDL_mixer.h>

class SoundLoader
{
public:
	Mix_Chunk* loadWAV(std::string file);
	Mix_Chunk* loadOGG(std::string file);
};

#endif