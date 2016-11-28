#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include "Sprite.h"
#include <functional>
#include "Text.h"

class Button : public Sprite
{
public:
	Button(SDL_Texture* texture, SDL_Renderer* renderer);

	void update();
	void render(SDL_Renderer* renderer);
	void onClick();

public:
	Text text;

public:
	std::function<void()> click;
};

#endif