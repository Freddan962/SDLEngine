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

Sprite::Sprite(const Sprite& other)
{
	mTexture = other.mTexture;

	SDL_Rect newBody;
	newBody.x = other.getBody()->x;
	newBody.y = other.getBody()->y;
	newBody.w = other.getBody()->w;
	newBody.h = other.getBody()->h;
	mBody = std::make_shared<SDL_Rect>(newBody);

	mTexture = other.getTexture();
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

std::shared_ptr<SDL_Rect> Sprite::getBody() const
{
	return mBody;
}

SDL_Texture* Sprite::getTexture() const
{
	return mTexture;
}