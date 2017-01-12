#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include <memory>

class Sprite
{
public:
	static Sprite* getInstance(SDL_Surface* surface, SDL_Renderer* renderer);

	virtual void update();
	virtual void render();
	virtual void onCollide(Sprite* sprite);

	void renderBodyOutline();
	void scale(double x, double y);

	void setRenderer(SDL_Renderer* renderer);
	void setBodyOutline(bool state);

	SDL_Surface* getSurface() const;
	SDL_Texture* getTexture() const;
	std::shared_ptr<SDL_Rect> getBody() const;

protected:
	Sprite(SDL_Surface* surface, SDL_Renderer* renderer);
	Sprite(const Sprite &other);

private:
	const Sprite& operator=(const Sprite& other) = delete;

protected:
	std::shared_ptr<SDL_Rect> mBody;
	SDL_Renderer* mRenderer;
	SDL_Surface* mSurface;
	SDL_Texture* mTexture;

private:
	bool mBodyOutline;
};

#endif