#include "Button.h"

Button::Button(SDL_Surface* surface, SDL_Renderer* renderer) 
	: Sprite(surface, renderer),
	text(renderer)
{
	text.setCutLimit(getBody()->w);
	mUpdatedText = false;
};

void Button::update()
{
	Sprite::update();

	if (!mUpdatedText)
	{
		updateTextPosition();
		mUpdatedText = true;
	}
}

void Button::render()
{
	Sprite::render();
	text.render();
}

void Button::onClick()
{
	if (click)
		click();
}

void Button::onMouseActive()
{
	if (mMouseHover) return;
	mMouseHover = true;

	onMouseEnter();
}

void Button::onMouseInactive()
{
	if (!mMouseHover) return;
	mMouseHover = false;

	onMouseLeave();
}

void Button::onMouseEnter()
{
	if (hasSecondarySurface()) swapSurfaces();
}

void Button::onMouseLeave()
{
	if (hasSecondarySurface()) swapSurfaces();
}

void Button::setSecondarySurface(SDL_Surface* surface)
{
	mSecondarySurface = surface;
	mSecondaryTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
}

bool Button::hasSecondarySurface()
{
	return mSecondaryTexture != nullptr;
}

void Button::swapSurfaces()
{
	SDL_Surface* auxSurface = mSurface;
	SDL_Texture* auxTexture = mTexture;

	mSurface = mSecondarySurface;
	mTexture = mSecondaryTexture;

	mSecondarySurface = auxSurface;
	mSecondaryTexture = auxTexture;
}

void Button::updateTextPosition()
{
	text.getBody()->x = getBody()->x + getBody()->w / 2 - text.getSize().x / 2;
	text.getBody()->y = getBody()->y + getBody()->h / 2 - text.getSize().y / 2;
}