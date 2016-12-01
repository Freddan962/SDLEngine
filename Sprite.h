#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include <memory>

class Sprite
{
public:
	Sprite(SDL_Surface* surface, SDL_Renderer* renderer);
	Sprite(const Sprite &other);

	virtual void update();
	virtual void render();
	virtual void onCollide(Sprite* sprite);

	void renderBodyOutline();

	void setRenderer(SDL_Renderer* renderer);
	void setBodyOutline(bool state);

	SDL_Surface* getSurface() const;
	SDL_Texture* getTexture() const;
	std::shared_ptr<SDL_Rect> getBody() const;

protected:
	std::shared_ptr<SDL_Rect> mBody;
	SDL_Renderer* mRenderer;

private:
	SDL_Surface* mSurface;
	SDL_Texture* mTexture;
	bool mBodyOutline;
};

#endif