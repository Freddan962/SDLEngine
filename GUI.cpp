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
	case SDL_TEXTINPUT:
		handleTextInput(event);
		break;
	case SDL_KEYDOWN:
		handleKeyDown(event);
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

	updateHover();
}

void GUI::GUI::updateHover()
{
	std::shared_ptr<SDL_Rect> click = getMousePos();

	for (itField iterator = mInputFields.begin(); iterator != mInputFields.end(); iterator++)
	{
		if (Physics::isRectangularCollision(iterator->second->getBody().get(), click.get()))
			iterator->second->onMouseActive();
		else
			iterator->second->onMouseInactive();
	}


	for (itButton iterator = mButtons.begin(); iterator != mButtons.end(); iterator++)
	{
		if (Physics::isRectangularCollision(iterator->second->getBody().get(), click.get()))
			iterator->second->onMouseActive();
		else
			iterator->second->onMouseInactive();
	}		
}

void GUI::GUI::renderElements(SDL_Renderer* renderer)
{
	for (itField iterator = mInputFields.begin(); iterator != mInputFields.end(); iterator++)
		iterator->second.get()->render();

	for (itButton iterator = mButtons.begin(); iterator != mButtons.end(); iterator++)
		iterator->second.get()->render();

	for (itSprite iterator = mSprites.begin(); iterator != mSprites.end(); iterator++)
		iterator->second.get()->render();
}

std::shared_ptr<SDL_Rect> GUI::GUI::getMousePos()
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
	handleElementInteraction(getMousePos());
}

void GUI::GUI::handleTextInput(SDL_Event* event)
{
	std::string text = event->text.text;

	for (itField iterator = mActiveInputFields.begin(); iterator != mActiveInputFields.end(); iterator++)
	{
		std::shared_ptr<InputField> field = iterator->second;
		field->text.appendText(text);
	}
}

void GUI::GUI::handleElementInteraction(std::shared_ptr<SDL_Rect> click)
{
	handleInputFieldInteraction(click);
		
	for (itButton iterator = mButtons.begin(); iterator != mButtons.end(); iterator++)
		if (Physics::isRectangularCollision(iterator->second->getBody().get(), click.get()))
			iterator->second.get()->onClick();
}

void GUI::GUI::handleInputFieldInteraction(std::shared_ptr<SDL_Rect> click)
{
	for (itField iterator = mInputFields.begin(); iterator != mInputFields.end(); iterator++)
	{
		std::shared_ptr<InputField> field = iterator->second;

		if (Physics::isRectangularCollision(field->getBody().get(), click.get()))
		{
			if (mActiveInputFields.find(iterator->first) == mActiveInputFields.end())
			{
				field->setActive(true);
				mActiveInputFields.insert(std::pair<std::string, std::shared_ptr<InputField>>(iterator->first, field));
			}
		}
		else if (field->isActive())
		{
			field->setActive(false);
			mActiveInputFields.erase(iterator->first);
		}
	}
}

void GUI::GUI::handleKeyDown(SDL_Event* event)
{
	if (event->key.keysym.sym != SDLK_BACKSPACE) return;

	for (itField iterator = mActiveInputFields.begin(); iterator != mActiveInputFields.end(); iterator++)
		iterator->second->text.removeLastCharacter();
}