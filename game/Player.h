#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../EntitySprite.h"
#include "../Vector2.h"
#include "../Timer.h"

class Projectile;
class Sound;

class Player : public EntitySprite
{
public:
	Player(SDL_Texture* texture);

	void update();
	void render(SDL_Renderer* renderer);

	void moveLeft();
	void moveRight();
	void stopMoveHorizontal();

	std::shared_ptr<Projectile> fire();
	bool canFire();

	void setProjectile(std::shared_ptr<Projectile> projectile);
	void setProjectileFiringSound(std::shared_ptr<Sound> sound);
	Vector2<float> getProjectileSpeed();
	
private:
	Vector2<float> mCurrSpeed;
	Timer mFireTimer;
	std::shared_ptr<Projectile> mProjectile;
	Vector2<float> mProjectileSpeed;
	std::shared_ptr<Sound> mProjectileFiringSound;
};

#endif