#ifndef POWERUP_H
#define POWERUP_H

#include "../Timer.h"
#include <memory>

enum POWER_TYPE {
	POWER_TYPE_SPEED = 1,
	POWER_TYPE_WORTH = 2
};

class Powerup : public EntitySprite
{
public:
	void setTarget(Sprite* target)
	{
		setCollidable(false);
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
			if (mTarget)
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

	bool isOver()
	{
		return mOver;
	}

	Sprite* getTarget()
	{
		return mTarget;
	}

protected:
	Powerup(SDL_Surface* surface, SDL_Renderer* renderer)
		: EntitySprite(surface, renderer), mOver(false) { }

	virtual void effectStart() = 0;
	virtual void effectOver() = 0;

private:
	Powerup(const Powerup& other) = delete;
	const Powerup& operator=(const Powerup& other) = delete;

protected:
	Timer mEffectDuration;
	Sprite* mTarget = nullptr;
	bool mOver;
};
#endif