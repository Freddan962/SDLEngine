#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "Button.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Timer.h"

class InputField : public Button
{
public:
	static InputField* getInstance(SDL_Surface* surface, SDL_Renderer* renderer);
	~InputField();

	void update();
	void render();

	void onActive();
	void onInactive();

	void appendText(std::string txt);
	void removeLastCharacter();
	void positionActiveText();
	bool isActive();

	void addInputIndicator();
	void removeInputIndicator();
	void updateIndicatorState();

	void setActive(bool active);

protected:
	InputField(SDL_Surface* surface, SDL_Renderer* renderer);

private:
	InputField(const InputField& other) = delete;
	const InputField& operator=(const InputField& other) = delete;

private:
	bool mActive;
	Text* mActiveText;
	std::string mActiveString;
	Timer mIndicatorTimer;
};

#endif