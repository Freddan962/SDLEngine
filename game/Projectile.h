#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../EntitySprite.h"

class Projectile : public EntitySprite
{
public:
	Projectile(SDL_Texture* texture) : EntitySprite(texture) {}
	Projectile(const Projectile& other);
};

#endif