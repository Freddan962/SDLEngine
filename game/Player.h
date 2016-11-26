#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../EntitySprite.h"
#include "../Vector2.h"
#include "../Timer.h"

class Projectile;

class Player : public EntitySprite
{
public:
	Player(SDL_Texture* texture);

	void update();
	void render(SDL_Renderer* renderer);

	void moveLeft();
	void moveRight();
	void fire();

private:
	Vector2<float> mCurrSpeed;
	Timer mFireTimer;
};

#endif