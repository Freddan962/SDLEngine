#include "InputField.h"
#include "Centerer.h"

InputField::InputField(SDL_Surface* surface, SDL_Renderer* renderer) 
	: Button(surface, renderer)
{
	mActiveText = Text::getInstance(renderer);
	mIndicatorTimer.setTime(450);
}

InputField* InputField::getInstance(SDL_Surface* surface, SDL_Renderer* renderer)
{
	return new InputField(surface, renderer);
}

InputField::~InputField() 
{
	delete mActiveText;
}

void InputField::update()
{
	Button::update();

	if (mIndicatorTimer.isReady())
		updateIndicatorState();
}

void InputField::render()
{
	Button::render();

	if (isActive() && text->getText().size() < text->getInputLimit())
		mActiveText->render();
}

void InputField::onActive()
{
	addInputIndicator();
	mIndicatorTimer.start();
}

void InputField::onInactive()
{
	removeInputIndicator();
}

void InputField::setActive(bool active) 
{ 
	mActive = active;

	if (mActive)
		onActive();
	else
		onInactive();
}

void InputField::appendText(std::string txt)
{
	text->appendText(txt);
	updateTextPosition();
	positionActiveText();
}

void InputField::removeLastCharacter()
{
	text->removeLastCharacter();
	updateTextPosition();
	positionActiveText();
}

void InputField::positionActiveText()
{
	Vector2<int> size;
	size.x = text->getBody()->x + text->getBody()->w;
	size.y = text->getBody()->y;

	if (text->getBody()->h == 0)
	{
		Vector2<int> adjustedSize;
		std::string str = "|";
		TTF_SizeText(text->getFont(), str.c_str(), &adjustedSize.x, &adjustedSize.y);
		size.y = text->getBody()->y - (adjustedSize.y / 2);
	}

	mActiveText->getBody()->x = size.x;
	mActiveText->getBody()->y = size.y;
}

void InputField::addInputIndicator()
{
	mActiveText->setFont(text->getFont());
	mActiveText->setText("|");

	updateTextPosition();
	positionActiveText();
}

void InputField::removeInputIndicator()
{
	mActiveText->removeLastCharacter();
}

void InputField::updateIndicatorState()
{
	if (mActiveText->getText().empty())
		addInputIndicator();
	else
		removeInputIndicator();

	mIndicatorTimer.reset();
	mIndicatorTimer.start();
}

bool InputField::isActive() { return mActive; }