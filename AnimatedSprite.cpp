#include "AnimatedSprite.h"

void AnimatedSprite::update()
{

}

void AnimatedSprite::render(SDL_Renderer* renderer)
{
	if (mAnimate)
		updateFrame();

	if (mTexture && mBody)
		SDL_RenderCopy(renderer, mTexture, NULL, mBody.get());
}

void AnimatedSprite::addFrame(SDL_Texture* frame)
{
	mFrames.push_back(frame);
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

		mTexture = mFrames.at(mAnimationIndex);
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