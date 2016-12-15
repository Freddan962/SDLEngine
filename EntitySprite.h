#ifndef ENTITYSPRITE_H
#define ENTITYSPRITE_H

#include "Sprite.h"
#include <memory>
#include "Vector2.h"
#include "Vector4.h"

class EntitySprite : public Sprite
{
public:
	EntitySprite(SDL_Surface* surface, SDL_Renderer* renderer)
		: Sprite(surface, renderer) {}

	EntitySprite(const EntitySprite& other);

	virtual void update();

	virtual void onLeftRestriction() {}
	virtual void onRightRestriction() {}
	virtual void onTopRestriction() {}
	virtual void onBottomRestriction() {}
	
	void updateMovement();

	Vector2<int> getSpeed() const;
	void setSpeed(int x, int y);
	void modSpeed(int x, int y);

	void setMovementRestriction(int x, int y, int w, int h);
	void setMovementRestriction(Vector4<int> restriction);
	Vector4<int> getMovementRestriction() const;

private:
	Vector2<int> mSpeed;
	Vector4<int> mRestriction;
};

#endif