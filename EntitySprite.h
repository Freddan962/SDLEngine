#ifndef ENTITYSPRITE_H
#define ENTITYSPRITE_H

#include "Sprite.h"
#include <memory>
#include "Vector2f.h"

struct Vector2f;

class EntitySprite : public Sprite
{
public:
	EntitySprite(SDL_Texture* texture)
		: Sprite(texture),
		mSpeed(new Vector2f) {}

	virtual void update();

	std::shared_ptr<Vector2f> getSpeed();
	void setSpeed(float x, float y);
	void modSpeed(float x, float y);

private:
	std::shared_ptr<Vector2f> mSpeed;
};

#endif