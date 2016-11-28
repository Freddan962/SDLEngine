#include "Button.h"

Button::Button(SDL_Texture* texture, SDL_Renderer* renderer) 
	: Sprite(texture),
	text(renderer)
{

};

void Button::update()
{
	Sprite::update();
	
	text.getBody()->x = getBody()->x + getBody()->w / 2 - text.getSize().x / 2;
	text.getBody()->y = getBody()->y + getBody()->h / 2 - text.getSize().y / 2;
}

void Button::render(SDL_Renderer* renderer)
{
	Sprite::render(renderer);
	text.render(renderer);
}

void Button::onClick()
{
	click();
}