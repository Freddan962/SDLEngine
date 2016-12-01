#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "Button.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <memory>
#include <string>

class InputField : public Button
{
public:
	InputField(SDL_Surface* surface, SDL_Renderer* renderer);

	void render();

	void setActive(bool active);
	bool isActive();

private:
	bool mActive;
};

#endif