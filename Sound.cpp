#include "Sound.h"

Sound::Sound(Mix_Chunk* sound)
{
	mSound = sound;
	mLoops = 0; //Play once
	mChannel = -1; //No channel
}

void Sound::play()
{
	mChannel = Mix_PlayChannel(-1, mSound, mLoops);
}

bool Sound::isPlaying()
{
	if (mChannel == -1) return false;
	return Mix_Playing(mChannel) != 0;
}

void Sound::pause()
{
	if (mChannel != -1)
		Mix_Pause(mChannel);
}

void Sound::resume()
{
	if (mChannel != -1)
		Mix_Resume(mChannel);
}

void Sound::stop()
{
	if (mChannel != 1)
		Mix_HaltChannel(-1);
}

void Sound::repeat()
{
	mLoops = -1;
}

void Sound::setLoops(int loops)
{
	mLoops = loops;
}

void Sound::setVolume(int volume)
{
	Mix_Volume(mChannel, volume);
}