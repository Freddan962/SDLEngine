#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../EntitySprite.h"

class Projectile : public EntitySprite
{
public:
	Projectile(SDL_Surface* surface, SDL_Renderer* renderer) : EntitySprite(surface, renderer) {}
	Projectile(const Projectile& other);
};

#endif