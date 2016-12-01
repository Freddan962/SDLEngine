#include "Sprite.h"
#include "SDL.h"

Sprite::Sprite(SDL_Surface* surface, SDL_Renderer* renderer)
	: mBody(new SDL_Rect())
{
	mSurface = surface;
	mRenderer = renderer;

	if (surface)
	{
		mBody->w = surface->w;
		mBody->h = surface->h;
	}

	if (surface && renderer)
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}
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

void Sprite::update()
{

}

void Sprite::render()
{
	if (mSurface && mBody)
		SDL_RenderCopy(mRenderer, mTexture, NULL, mBody.get());
}

void Sprite::onCollide(Sprite* sprite)
{

}

void Sprite::setRenderer(SDL_Renderer* renderer)
{
	mRenderer = renderer;
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