#include "InputField.h"

InputField::InputField(SDL_Texture* texture, SDL_Renderer* renderer) 
	: Button(texture, renderer)
{

}

void InputField::render(SDL_Renderer* renderer)
{
	Button::render(renderer);
}

void InputField::setActive(bool active) { mActive = active; }
bool InputField::isActive() { return mActive; }