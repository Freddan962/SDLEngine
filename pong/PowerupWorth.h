#ifndef POWERUPWORTH_H
#define POWERUPWORTH_H

#include "Powerup.h"
#include "Ball.h"

class PowerupWorth : public Powerup
{
public:
	static PowerupWorth* getInstance(SDL_Surface* surface, SDL_Renderer* renderer)
	{
		return new PowerupWorth(surface, renderer);
	}

	void onCollide(Sprite* sprite)
	{
		if (mTarget) return;

		if (Ball* ball = dynamic_cast<Ball*>(sprite))
			setTarget(ball);
	}

private:
	PowerupWorth(SDL_Surface* surface, SDL_Renderer* renderer) : Powerup(surface, renderer)
	{
		mEffectDuration.setTime(3000);
	}

	void effectStart()
	{
		Ball* ball = dynamic_cast<Ball*>(mTarget);
		if (!ball) return;
		
		ball->setScoreWorth(2);
	};

	void effectOver()
	{
		if (!mTarget) return;

		Ball* ball = dynamic_cast<Ball*>(mTarget);
		if (!ball) return;

		ball->setScoreWorth(1);
		mOver = true;
	};
};

#endif