#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SDL.h"
#include "Sprite.h"
#include <vector>

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(SDL_Texture* texture) : Sprite(texture) 
	{ 
		mAnimationSpeed = 100;
		mAnimationCounter = 0;
		mAnimationIndex = 0;
		mTexture = texture;
		mFrames.push_back(texture);
	};

	void update();
	void render(SDL_Renderer* renderer);
	void addFrame(SDL_Texture* frame);

	void setAnimationSpeed(int speed);
	void disableAnimation();
	void enableAnimation();

private:
	void updateFrame();

private:
	SDL_Texture* mTexture;
	std::vector<SDL_Texture*> mFrames;
	int mAnimationSpeed;
	int mAnimationCounter;
	int mAnimationIndex;
	bool mAnimate;
};

#endif