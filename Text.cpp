#include "Text.h"

Text::Text(SDL_Renderer* renderer)
	: Sprite(NULL, renderer)
{
	mRenderer = renderer;
	setColor(255, 255, 255);
	mTextTexture = nullptr;
}

Text* Text::getInstance(SDL_Renderer* renderer)
{
	return new Text(renderer);
}

Text::~Text()
{
	SDL_DestroyTexture(mTextTexture);
}

void Text::render()
{
	if (mRenderer && mTextTexture)
		SDL_RenderCopy(mRenderer, mTextTexture, NULL, mBody.get());
}

void Text::setText(std::string text)
{
	mText = text;
	constructVisuals();
}

void Text::setFont(TTF_Font* font)
{
	mFont = font;
}

void Text::appendText(std::string text)
{
	mText = mText.append(text);
	constructVisuals();
}

void Text::removeLastCharacter()
{
	setText(mText.substr(0, mText.size() - 1));
}

void Text::constructVisuals()
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(mFont, mText.c_str(), mTextColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);

	if (mTextTexture)
		SDL_DestroyTexture(mTextTexture);

	adjustBodyForText();

	mTextTexture = textTexture;
	SDL_FreeSurface(textSurface);
}

void Text::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	mTextColor = { r, g, b };
}

void Text::adjustBodyForText()
{
	Vector2<int> size = getSize();
	getBody()->w = size.x;
	getBody()->h = size.y;
}

Vector2<int> Text::getSize()
{
	Vector2<int> size;
	if (mText.empty()) return size;

	TTF_SizeText(mFont, mText.c_str(), &size.x, &size.y);
	return size;
}

std::string Text::getText()
{
	return mText;
}

TTF_Font* Text::getFont()
{
	return mFont;
}