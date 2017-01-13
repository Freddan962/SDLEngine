#include "Sprite.h"
#include "SDL.h"

Sprite::Sprite(SDL_Surface* surface, SDL_Renderer* renderer)
	: mBody(new SDL_Rect()), mCollidable(false)
{
	mSurface = surface;
	mRenderer = renderer;

	if (surface)
	{
		mBody->w = surface->w;
		mBody->h = surface->h;
	}

	if (surface && renderer)
		mTexture = SDL_CreateTextureFromSurface(renderer, surface);
}


Sprite::Sprite(const Sprite& other)
{
	mSurface = other.mSurface;

	SDL_Rect newBody;
	newBody.x = other.getBody()->x;
	newBody.y = other.getBody()->y;
	newBody.w = other.getBody()->w;
	newBody.h = other.getBody()->h;
	mBody = std::make_shared<SDL_Rect>(newBody);

	mSurface = other.getSurface();
}

Sprite* Sprite::getInstance(SDL_Surface* surface, SDL_Renderer* renderer)
{
	return new Sprite(surface, renderer);
}

bool Sprite::mBodyOutline = false;

void Sprite::update()
{

}

void Sprite::render()
{
	if (mSurface && mBody)
		SDL_RenderCopy(mRenderer, mTexture, NULL, mBody.get());

	if (mBodyOutline)
		renderBodyOutline();
}

void Sprite::onCollide(Sprite* sprite)
{

}

void Sprite::renderBodyOutline()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 0);
	SDL_RenderDrawRect(mRenderer, mBody.get());
}

void Sprite::setRenderer(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

void Sprite::setBodyOutline(bool state)
{
	mBodyOutline = state;
}

std::shared_ptr<SDL_Rect> Sprite::getBody() const
{
	return mBody;
}

SDL_Surface* Sprite::getSurface() const
{
	return mSurface;
}

SDL_Texture* Sprite::getTexture() const
{
	return mTexture;
}

void Sprite::scale(double x, double y)
{
	mBody->w = mBody->w * x;
	mBody->h = mBody->h * y;
	mScale.x = x;
	mScale.y = y;
}

Vector2<double> Sprite::getScale()
{
	return mScale;
}

void Sprite::setCollidable(bool collidable)
{
	mCollidable = collidable;
}

bool Sprite::isCollidable()
{
	return mCollidable;
}

Vector2<float> Sprite::getCenter()
{
	Vector2<float> center;
	center.x = getBody()->x + getBody()->w / 2;
	center.y = getBody()->y + getBody()->h / 2;

	return center;
}