#include "InputField.h"

InputField::~InputField()
{
	SDL_DestroyTexture(mTextTexture);
}

void InputField::render(SDL_Renderer* renderer)
{
	if (renderer && mTextTexture)
		SDL_RenderCopy(renderer, mTextTexture, NULL, mBody.get());
}

void InputField::setText(std::string text)
{
	mText = text;
	constructVisuals();
}

void InputField::setFontSize(int size)
{
	TTF_Font* pFont = TTF_OpenFont("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\vertigo.ttf", size);
	mFont = pFont;
	constructVisuals();
}

void InputField::constructVisuals()
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(mFont, mText.c_str(), mTextColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
	
	if (mTextTexture)
		SDL_DestroyTexture(mTextTexture);
	
	mTextTexture = textTexture;
	SDL_FreeSurface(textSurface);
}