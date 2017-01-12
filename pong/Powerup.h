#ifndef POWERUP_H
#define POWERUP_H

#include "../Timer.h"
#include <memory>

enum POWER_TYPE {
	POWER_TYPE_SPEED = 1,
	POWER_TYPE_SIZE = 2
};

class Powerup : public EntitySprite
{
public:
	void setTarget(Sprite* target)
	{
		mTarget = target;
		mEffectDuration.start();
		effectStart();
	}

	void update()
	{
		EntitySprite::update();

		if (mEffectDuration.isReady())
		{
			mEffectDuration.stop();
			effectOver();
		}
	}

	void render()
	{
		if (!isUsed())
			EntitySprite::render();
	}

	bool isUsed()
	{
		return mTarget != nullptr;
	}

protected:
	Powerup(SDL_Surface* surface, SDL_Renderer* renderer)
		: EntitySprite(surface, renderer) 
	{
 		mCollisionCheckTimer.setTime(500);
		mCollisionCheckTimer.start();
	}

	virtual void effectStart() = 0;
	virtual void effectOver() = 0;

private:
	Powerup(const Powerup& other) = delete;
	const Powerup& operator=(const Powerup& other) = delete;

protected:
	Timer mEffectDuration;
	Timer mCollisionCheckTimer;
	Sprite* mTarget = nullptr;
};
#endif