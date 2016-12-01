#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include "Sprite.h"
#include <functional>
#include "LimitedText.h"

class Button : public Sprite
{
public:
	Button(SDL_Texture* texture, SDL_Renderer* renderer);

	void update();
	void render(SDL_Renderer* renderer);
	void onClick();

public: 
	LimitedText text;
	std::function<void()> click;

private:
	std::string mActualText;
};

#endif