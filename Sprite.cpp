#include "Sprite.h"
#include "SDL.h"

Sprite::Sprite(SDL_Texture* texture)
	: mBody(new SDL_Rect())
{
	mTexture = texture;

	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	mBody->w = width;
	mBody->h = height;
}

void Sprite::update()
{

}

void Sprite::render(SDL_Renderer* renderer)
{
	if (mTexture && mBody)
		SDL_RenderCopy(renderer, mTexture, NULL, mBody.get());
}

void Sprite::onCollide(Sprite* sprite)
{

}

std::shared_ptr<SDL_Rect> Sprite::getBody()
{
	return mBody;
}