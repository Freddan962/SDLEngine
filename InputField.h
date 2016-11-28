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
	InputField(SDL_Texture* texture, SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer);

	void setActive(bool active);
	bool isActive();

private:
	bool mActive;
};

#endif