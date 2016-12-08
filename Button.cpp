#include "Button.h"

Button::Button(SDL_Surface* surface, SDL_Renderer* renderer) 
	: Sprite(surface, renderer),
	text(renderer)
{
	text.setCutLimit(getBody()->w);
};

void Button::update()
{
	Sprite::update();
	
	text.getBody()->x = getBody()->x + getBody()->w / 2 - text.getSize().x / 2;
	text.getBody()->y = getBody()->y + getBody()->h / 2 - text.getSize().y / 2;
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