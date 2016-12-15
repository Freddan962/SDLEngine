#ifndef BALL_H
#define BALL_H

#include "../EntitySprite.h"

class Ball : public EntitySprite
{
public:
	Ball(SDL_Surface* surface, SDL_Renderer* renderer) : EntitySprite(surface, renderer) {}
	
	void onCollide(Sprite* sprite);
	void onLeftRestriction();
	void onRightRestriction();
	void onTopRestriction();
	void onBottomRestriction();
};

#endif