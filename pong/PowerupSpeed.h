#ifndef POWERUPSPEED_H
#define POWERUPSPEED_H

#include "Powerup.h"
#include "Ball.h"

class PowerupSpeed : public Powerup
{
public:
	static PowerupSpeed* getInstance(SDL_Surface* surface, SDL_Renderer* renderer)
	{
		return new PowerupSpeed(surface, renderer);
	}

	void onCollide(Sprite* sprite)
	{
		if (mTarget) return;

 		if (Ball* ball = dynamic_cast<Ball*>(sprite))
			setTarget(ball);
	}

private:
	PowerupSpeed(SDL_Surface* surface, SDL_Renderer* renderer) : Powerup(surface, renderer) 
	{
		mEffectDuration.setTime(5000);
	}

	void effectStart()
	{ 
		Ball* ball = dynamic_cast<Ball*>(mTarget);
		if (!ball) return;

		speedBefore.x = ball->getVelocity().x;
		speedBefore.y = ball->getVelocity().y;

		Vector2<int> newSpeed;
		newSpeed.x = ball->getVelocity().x * 2;
		newSpeed.y = ball->getVelocity().y * 2;

		if (speedBefore.y < 0)
			newSpeed.y *= 1;

		if (speedBefore.x < 0)
			newSpeed.x *= 1;

		ball->setVelocity(newSpeed.x, newSpeed.y);
	};

	void effectOver() 
	{
		if (!mTarget) return;
		Ball* ball = dynamic_cast<Ball*>(mTarget);
		if (!ball) return;

		if (ball->getVelocity().x < 0 && speedBefore.x > 0)
			speedBefore.x *= -1;

		if (ball->getVelocity().y < 0 && speedBefore.y > 0)
			speedBefore.y *= -1;

		ball->setVelocity(speedBefore.x, speedBefore.y);
		mOver = true;
	};

private:
	Vector2<int> speedBefore;
};

#endif