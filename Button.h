#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include "Sprite.h"
#include <functional>
#include "LimitedText.h"

class Button : public Sprite
{
public:
	static Button* getInstance(SDL_Surface* surface, SDL_Renderer* renderer);

	void update();
	void render();

	void swapSurfaces();
	bool hasSecondarySurface();
	void updateTextPosition();

	void onClick();
	void onMouseActive();
	void onMouseInactive();
	void onMouseEnter();
	void onMouseLeave();

	void setSecondarySurface(SDL_Surface* surface);

protected:
	Button(SDL_Surface* surface, SDL_Renderer* renderer);

private:
	Button(const Button& other) = delete;
	const Button& operator=(const Button& other) = delete;

public: 
	LimitedText text;
	std::function<void()> click;

	bool mMouseHover;
	SDL_Surface* mSecondarySurface;
	SDL_Texture* mSecondaryTexture;

	bool mUpdatedText;
};

#endif