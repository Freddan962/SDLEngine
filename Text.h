#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SDL_ttf.h"
#include "Sprite.h"
#include "Vector2.h"

class Text : public Sprite
{
public:
	Text(SDL_Renderer* renderer);
	~Text();

	void render();

	void appendText(std::string text);
	void removeLastCharacter();
	void constructVisuals();

	void setText(std::string text);
	void setFont(TTF_Font* font);
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	Vector2<int> getSize();
	std::string getText();
	TTF_Font* getFont();

private:
	void adjustBodyForText();

private:
	SDL_Color mTextColor;
	TTF_Font* mFont;
	SDL_Texture* mTextTexture;
	SDL_Renderer* mRenderer;

protected:
	std::string mText;
};

#endif