#ifndef BALL_H
#define BALL_H

#include "../AnimatedSprite.h"

class Ball : public AnimatedSprite
{
public:
	Ball(SDL_Surface* surface, SDL_Renderer* renderer) : AnimatedSprite(surface, renderer) {}
	
	void onCollide(Sprite* sprite);
	void onLeftRestriction();
	void onRightRestriction();
	void onTopRestriction();
	void onBottomRestriction();

private:
	void invertHorizontalSpeed();
	void invertVerticalSpeed();

};

#endif