#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include <memory>

class Sprite
{
public:
	Sprite(SDL_Texture* texture);
	Sprite(const Sprite &other);

	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	virtual void onCollide(Sprite* sprite);

	SDL_Texture* getTexture() const;
	std::shared_ptr<SDL_Rect> getBody() const;

protected:
	std::shared_ptr<SDL_Rect> mBody;

private:
	SDL_Texture* mTexture;
};

#endif