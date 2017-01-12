#ifndef POWERUPSPEED_H
#define POWERUPSPEED_H

#include "Powerup.h"
#include "Ball.h"
#include <iostream>

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

  		if (mCollisionCheckTimer.isReady())
		{
			if (Ball* ball = dynamic_cast<Ball*>(sprite))
			{
				setTarget(ball);
				mCollisionCheckTimer.reset();
			}
		}
	}

private:
	PowerupSpeed(SDL_Surface* surface, SDL_Renderer* renderer) : Powerup(surface, renderer) 
	{
		mEffectDuration.setTime(5000);
	}

	void effectStart()
	{ 
		std::cout << "STARTED start" << std::endl;
		Ball* ball = dynamic_cast<Ball*>(mTarget);
		if (!ball) return;

		ball->setSpeed(ball->getSpeed().x * 2, ball->getSpeed().x * 2);
		std::cout << "STARTED end" << std::endl;
	};

	void effectOver() 
	{
		std::cout << "END START" << std::endl;

		Ball* ball = dynamic_cast<Ball*>(mTarget);
		if (!ball) return;

		ball->setSpeed(ball->getSpeed().x / 2, ball->getSpeed().y / 2);

		std::cout << "END END" << std::endl;
	};
};

#endif