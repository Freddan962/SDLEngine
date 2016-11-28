#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SDL_ttf.h"
#include "Sprite.h"

class Text : public Sprite
{
public:
	Text(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer);

	void appendText(std::string text);
	void constructVisuals();

	void setText(std::string text);
	void setFont(TTF_Font* font);
	void setColor(Uint8 r, Uint8 g, Uint8 b);

private:
	void adjustBodyForText(std::string text);

private:
	std::string mText;
	TTF_Font* mFont;
	SDL_Color mTextColor;
	SDL_Texture* mTextTexture;
	SDL_Renderer* mRenderer;
};

#endif