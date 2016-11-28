#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "Sprite.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <memory>
#include <string>

class InputField : public Sprite
{
public:
	InputField(SDL_Texture* texture, SDL_Renderer* renderer) :
		Sprite(texture)
	{
		mRenderer = renderer;
		mText = "";
		mTextColor = { 255, 255, 255 };
		mFont = TTF_OpenFont("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\vertigo.ttf", 24);
		mTextTexture = nullptr;
		constructVisuals();
	}

	~InputField();

	void render(SDL_Renderer* renderer);

	void setText(std::string text);
	void appendText(std::string text);
	void setFontSize(int size);

	void setActive(bool active);
	bool getActive();

private:
	void constructVisuals();

private:
	std::string mText;
	TTF_Font* mFont;
	SDL_Color mTextColor;
	SDL_Texture* mTextTexture;
	SDL_Renderer* mRenderer;

	bool mActive;
};

#endif