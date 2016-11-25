#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include "Sprite.h"


class Button : public Sprite
{
public:
	Button(SDL_Texture* texture) : Sprite(texture) {}

	void onClick();

public:
	void(*click)();
};

#endif