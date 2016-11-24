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

	std::shared_ptr<SDL_Rect> getBody();

protected:
	std::shared_ptr<SDL_Rect> mBody;

private:
	SDL_Texture* mTexture;
};

#endif