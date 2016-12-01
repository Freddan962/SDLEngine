#include "InputField.h"

InputField::InputField(SDL_Surface* surface, SDL_Renderer* renderer) 
	: Button(surface, renderer)
{

}

void InputField::render()
{
	Button::render();
}

void InputField::setActive(bool active) { mActive = active; }
bool InputField::isActive() { return mActive; }