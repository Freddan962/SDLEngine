#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include <memory>
#include "Vector2.h"

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
	static void setBodyOutline(bool state);

	SDL_Surface* getSurface() const;
	SDL_Texture* getTexture() const;
	std::shared_ptr<SDL_Rect> getBody() const;
	Vector2<double> getScale();

	void setCollidable(bool collidable);
	bool isCollidable();

	Vector2<float> getCenter();

protected:
	Sprite(SDL_Surface* surface, SDL_Renderer* renderer);
	Sprite(const Sprite &other);

private:
	const Sprite& operator=(const Sprite& other) = delete;

public:
	static bool mBodyOutline;

protected:
	std::shared_ptr<SDL_Rect> mBody;
	SDL_Renderer* mRenderer;
	SDL_Surface* mSurface;
	SDL_Texture* mTexture;

private:
	Vector2<double> mScale;
	bool mCollidable;
};

#endif