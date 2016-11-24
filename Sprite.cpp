#include "Sprite.h"
#include "SDL.h"

Sprite::Sprite(SDL_Texture* texture)
	: mRect(new SDL_Rect())
{
	mTexture = texture;
}

void Sprite::update()
{

}

void Sprite::render(SDL_Renderer* renderer)
{
	if (mTexture && mRect)
		SDL_RenderCopy(renderer, mTexture, NULL, mRect.get());
}