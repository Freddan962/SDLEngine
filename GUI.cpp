#include "GUI.h"
#include "InputField.h"
#include "Button.h"
#include "Sprite.h"
#include "Vector2.h"
#include "Physics.h"
#include <iostream>

typedef std::map<std::string, std::shared_ptr<InputField>>::iterator itField;
typedef std::map<std::string, std::shared_ptr<Button>>::iterator itButton;
typedef std::map<std::string, std::shared_ptr<Sprite>>::iterator itSprite;

GUI::GUI::GUI()
{
	mCursorSize.x = 16;
	mCursorSize.y = 16;
}

void GUI::GUI::render(SDL_Renderer* renderer)
{
	renderElements(renderer);
}

void GUI::GUI::update()
{
	updateElements();
}

void GUI::GUI::handleEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		handleMouseButtonDown(event);
		break;
	}
}

void GUI::GUI::add(std::string name, std::shared_ptr<InputField> field)
{
	if (mInputFields.find(name) != mInputFields.end()) return;
	mInputFields.insert(std::pair<std::string, std::shared_ptr<InputField>>(name, field));
}

void GUI::GUI::add(std::string name, std::shared_ptr<Button> button)
{
	if (mButtons.find(name) != mButtons.end()) return;
	mButtons.insert(std::pair<std::string, std::shared_ptr<Button>>(name, button));
}

void GUI::GUI::add(std::string name, std::shared_ptr<Sprite> sprite)
{
	if (mSprites.find(name) != mSprites.end()) return;
	mSprites.insert(std::pair<std::string, std::shared_ptr<Sprite>>(name, sprite));
}

void GUI::GUI::updateElements()
{
	for (itField iterator = mInputFields.begin(); iterator != mInputFields.end(); iterator++)
		iterator->second.get()->update();

	for (itButton iterator = mButtons.begin(); iterator != mButtons.end(); iterator++)
		iterator->second.get()->update();

	for (itSprite iterator = mSprites.begin(); iterator != mSprites.end(); iterator++)
		iterator->second.get()->update();
}

void GUI::GUI::renderElements(SDL_Renderer* renderer)
{
	for (itField iterator = mInputFields.begin(); iterator != mInputFields.end(); iterator++)
		iterator->second.get()->render(renderer);

	for (itButton iterator = mButtons.begin(); iterator != mButtons.end(); iterator++)
		iterator->second.get()->render(renderer);

	for (itSprite iterator = mSprites.begin(); iterator != mSprites.end(); iterator++)
		iterator->second.get()->render(renderer);
}

std::shared_ptr<SDL_Rect> GUI::GUI::getMouseClick()
{
	Vector2<int> mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	std::shared_ptr<SDL_Rect> rect(new SDL_Rect());
	rect->x = mousePos.x;
	rect->y = mousePos.y;
	rect->w = mCursorSize.x;
	rect->h = mCursorSize.y;

	return rect;
}

void GUI::GUI::handleMouseButtonDown(SDL_Event* event)
{
	handleElementInteraction(getMouseClick());
}

void GUI::GUI::handleElementInteraction(std::shared_ptr<SDL_Rect> click)
{
	/*for (itField iterator = mInputFields.begin(); iterator != mInputFields.end(); iterator++)
		iterator->second.get()->*/

	for (itButton iterator = mButtons.begin(); iterator != mButtons.end(); iterator++)
		if (Physics::isRectangularCollision(iterator->second->getBody().get(), click.get()))
			iterator->second.get()->onClick();
}