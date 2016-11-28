#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"

class Sound
{
public:
	Sound(Mix_Chunk* sound);

	void play();
	bool isPlaying();

	void pause();
	void resume();
	void repeat();
	void stop();

	void setLoops(int loops);
	void setVolume(int volume);
private:
	Mix_Chunk* mSound;
	int mLoops;
	int mChannel;
};

#endif