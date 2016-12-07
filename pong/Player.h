#ifndef PLAYER_H
#define PLAYER_H

#include "../EntitySprite.h"
#include <string>

class Player : public EntitySprite {
public:
	Player(SDL_Surface* surface, SDL_Renderer* renderer) : EntitySprite(surface, renderer) {};

	std::string getName();
	void setName(std::string name);
private:

private:
	std::string mName;

};

#endif