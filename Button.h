#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include "Sprite.h"
#include <functional>

class Button : public Sprite
{
public:
	Button(SDL_Texture* texture) : Sprite(texture) {}

	void onClick();

public:
	std::function<void()> click;
};

#endif