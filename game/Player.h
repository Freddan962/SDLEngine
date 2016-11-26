#ifndef PLAYER_H
#define PLAYER_H

#include "../EntitySprite.h"
#include "../Vector2.h"

class Player : public EntitySprite
{
public:
	Player(SDL_Texture* texture);

	void update();

	void moveLeft();
	void moveRight();


private:
	Vector2<float> mCurrSpeed;
};

#endif