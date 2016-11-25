#ifndef ENTITYSPRITE_H
#define ENTITYSPRITE_H

#include "Sprite.h"
#include <memory>
#include "Vector2.h"

class EntitySprite : public Sprite
{
public:
	EntitySprite(SDL_Texture* texture)
		: Sprite(texture),
		mSpeed(new Vector2<float>) {}

	virtual void update();

	std::shared_ptr<Vector2<float>> getSpeed();
	void setSpeed(float x, float y);
	void modSpeed(float x, float y);

private:
	std::shared_ptr<Vector2<float>> mSpeed;
};

#endif