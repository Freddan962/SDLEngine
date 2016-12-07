#include "LimitedText.h"
#include "SDL.h"

LimitedText::LimitedText(SDL_Renderer* renderer)
	: Text(renderer) { }

void LimitedText::render()
{
	Text::render();
}

void LimitedText::setText(std::string text)
{
	updateText(text);
	constructVisuals();
}

void LimitedText::appendText(std::string text)
{
	updateText(mActualText.append(text));
	constructVisuals();
}

void LimitedText::removeLastCharacter()
{
	setText(mActualText.substr(0, mActualText.size() - 1));
}

bool LimitedText::isEmpty()
{
	return mActualText.empty();
}

std::string LimitedText::getText()
{
	return mActualText;
}

int LimitedText::getTextLimit()
{
	return mLimit;
}

void LimitedText::setTextLimit(int limit)
{
	mLimit = limit;
}

bool LimitedText::shouldCut(std::string text)
{
	std::string aux = mText;
	mText = text;
	bool shouldCut = getSize().x > mLimit;
	mText = aux;
	return shouldCut;
}

void LimitedText::cut()
{
	std::string cutText = mActualText;
	
	do {
		if (cutText.size() > 1)
			cutText = cutText.substr(1, cutText.size() - 1);
	} while (shouldCut(cutText));

	cutText[0] = '.';
	cutText[1] = '.';

	mText = cutText;
}

void LimitedText::updateText(std::string text)
{
	mActualText = text;
	if (shouldCut(mActualText))
		cut();
	else
		mText = mActualText;
}
