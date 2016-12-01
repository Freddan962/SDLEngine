#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SDL.h"
#include "Sprite.h"
#include <vector>

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(SDL_Surface* surface, SDL_Renderer* renderer) : Sprite(surface, renderer) 
	{ 
		mAnimationSpeed = 100;
		mAnimationCounter = 0;
		mAnimationIndex = 0;
		mSurface = surface;
		mFrames.push_back(surface);
	};

	void update();
	void render();
	void addFrame(SDL_Surface* frame);
	void setFrameIndex(int index);

	void setAnimationSpeed(int speed);
	void disableAnimation();
	void enableAnimation();

private:
	void updateFrame();

private:
	SDL_Surface* mSurface;
	std::vector<SDL_Surface*> mFrames;
	int mAnimationSpeed;
	int mAnimationCounter;
	int mAnimationIndex;
	bool mAnimate;
};

#endif