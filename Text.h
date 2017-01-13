#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SDL_ttf.h"
#include "Sprite.h"
#include "Vector2.h"

class Text : public Sprite
{
public:
	static Text* getInstance(SDL_Renderer* renderer);
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
protected:
	Text(SDL_Renderer* renderer);

private:
	void adjustBodyForText();
	Text(const Text& other) = delete;
	const Text& operator=(const Text& other) = delete;

private:
	SDL_Color mTextColor;
	TTF_Font* mFont;
	SDL_Texture* mTextTexture;
	SDL_Renderer* mRenderer;

protected:
	std::string mText;
};

#endif