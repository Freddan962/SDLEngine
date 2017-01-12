#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SDL.h"
#include "EntitySprite.h"
#include <vector>

class AnimatedSprite : public EntitySprite
{
public:
	static AnimatedSprite* getInstance(SDL_Surface* surface, SDL_Renderer* renderer);

	void update();
	void render();
	void addFrame(SDL_Surface* frame);
	void setFrameIndex(int index);

	void setAnimationSpeed(int speed);
	void disableAnimation();
	void enableAnimation();

protected:
	AnimatedSprite(SDL_Surface* surface, SDL_Renderer* renderer) : EntitySprite(surface, renderer)
	{
		mAnimationSpeed = 100;
		mAnimationCounter = 0;
		mAnimationIndex = 0;
		mSurface = surface;
		mFrames.push_back(surface);
	};

private:
	AnimatedSprite(const AnimatedSprite& other) = delete;
	const AnimatedSprite& operator=(const AnimatedSprite& other) = delete;
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