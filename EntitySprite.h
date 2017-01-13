#ifndef ENTITYSPRITE_H
#define ENTITYSPRITE_H

#include "Sprite.h"
#include <memory>
#include "Vector2.h"
#include "Vector4.h"

class EntitySprite : public Sprite
{
public:
	static EntitySprite* getInstance(SDL_Surface* surface, SDL_Renderer* renderer);

	virtual void update();

	virtual void onLeftRestriction() {}
	virtual void onRightRestriction() {}
	virtual void onTopRestriction() {}
	virtual void onBottomRestriction() {}
	virtual void onCollide(Sprite* sprite);
	
	void updateMovement();
	void updateMovement(double modX, double modY);

	Vector2<double> getVelocity() const;
	void setVelocity(double x, double y);
	void modVelocity(double x, double y);

	void setMovementRestriction(int x, int y, int w, int h);
	void setMovementRestriction(Vector4<int> restriction);
	Vector4<int> getMovementRestriction() const;

	bool isMoving();
	double getElasticity();
	void setElasticity(double elasticity);

	bool affectedByGravity();
	void setAffectedByGravity(bool affected);

	bool affectedByCollision();
	void setAffectedByCollision(bool affected);

protected:
	EntitySprite(SDL_Surface* surface, SDL_Renderer* renderer)
		: Sprite(surface, renderer), mAffectedByGravity(false), mElasticity(1), mCollisionSinceLastFrame(false)
		, mAffectedByCollision(true) {}

private:
	EntitySprite(const EntitySprite& other);
	const EntitySprite& operator=(const EntitySprite& other) = delete;
	void updateGravity();

private:
	Vector2<double> mVelocity;
	Vector4<int> mRestriction;
	double mElasticity;
	bool mAffectedByGravity;
	bool mCollisionSinceLastFrame;
	bool mAffectedByCollision;

};

#endif