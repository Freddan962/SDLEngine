#ifndef ENTITYSPRITE_H
#define ENTITYSPRITE_H

#include "Sprite.h"
#include <memory>
#include "Vector2.h"
#include "Vector4.h"

class EntitySprite : public Sprite
{
public:
	EntitySprite(SDL_Texture* texture)
		: Sprite(texture),
		mSpeed(new Vector2<int>) {}

	virtual void update();
	void updateMovement();

	std::shared_ptr<Vector2<int>> getSpeed();
	void setSpeed(int x, int y);
	void modSpeed(int x, int y);

	void setMovementRestriction(std::shared_ptr<Vector4<int>> restriction);

private:
	std::shared_ptr<Vector2<int>> mSpeed;
	//x = left, z = right
	//y = top, o = bottom
	std::shared_ptr<Vector4<int>> mRestriction;
};

#endif