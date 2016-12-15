#include "AnimatedSprite.h"

void AnimatedSprite::update()
{
	EntitySprite::update();
}

void AnimatedSprite::render()
{
	if (mAnimate)
		updateFrame();

	if (mSurface && mBody)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
		SDL_RenderCopy(mRenderer, texture, NULL, mBody.get());
		SDL_DestroyTexture(texture);
	}
}

void AnimatedSprite::addFrame(SDL_Surface* frame)
{
	mFrames.push_back(frame);
}

void AnimatedSprite::setFrameIndex(int index)
{
	mSurface = mFrames.at(index);
}

void AnimatedSprite::setAnimationSpeed(int speed)
{
	mAnimationSpeed = speed;
}

void AnimatedSprite::updateFrame()
{
	mAnimationCounter += 1;

	if (mAnimationCounter >= mAnimationSpeed)
	{
		if (mAnimationIndex + 1 > mFrames.size() - 1)
			mAnimationIndex = 0;
		else
			mAnimationIndex += 1;

		mSurface = mFrames.at(mAnimationIndex);
		mAnimationCounter = 0;
	}
}

void AnimatedSprite::disableAnimation()
{
	mAnimate = false;
}

void AnimatedSprite::enableAnimation()
{
	mAnimate = true;
}