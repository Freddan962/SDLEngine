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
	
	void updateMovement();

	/*Vector2<int> getSpeed() const;
	void setSpeed(int x, int y);
	void modSpeed(int x, int y);*/

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

protected:
	EntitySprite(SDL_Surface* surface, SDL_Renderer* renderer)
		: Sprite(surface, renderer) {}

private:
	EntitySprite(const EntitySprite& other);
	const EntitySprite& operator=(const EntitySprite& other) = delete;
	void updateGravity();

private:
	Vector2<double> mVelocity;
	//Vector2<int> mSpeed;
	Vector4<int> mRestriction;
	double mElasticity;
	bool mAffectedByGravity;

};

#endif