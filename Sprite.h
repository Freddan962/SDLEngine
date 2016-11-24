#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include <memory>

class Sprite
{
public:
	Sprite(SDL_Texture* texture);

	virtual void update();
	virtual void render(SDL_Renderer* renderer);

private:
	SDL_Texture* mTexture;
	std::shared_ptr<SDL_Rect> mRect;
};

#endif