#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "Button.h"
#include "SDL.h"
#include "SDL_ttf.h"

class InputField : public Button
{
public:
	InputField(SDL_Surface* surface, SDL_Renderer* renderer);

	void update();
	void render();

	void onActive();
	void onInactive();

	void appendText(std::string txt);
	void removeLastCharacter();
	void positionActiveText();
	bool isActive();
	void setActive(bool active);

private:
	bool mActive;
	Text mActiveText;
	std::string mActiveString;
};

#endif