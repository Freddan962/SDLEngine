#ifndef LIMITEDTEXT_H
#define LIMITEDTEXT_H

#include "Text.h"

class LimitedText : public Text
{
public:
	LimitedText(SDL_Renderer* renderer);

	void render();

	void appendText(std::string text);
	void removeLastCharacter();
	bool isEmpty();
	void setText(std::string text);
	std::string getText();

	int getTextLimit();
	void setTextLimit(int limit);

private:
	void cut();
	bool shouldCut(std::string text);
	void updateText(std::string text);

private:
	int mLimit;
	std::string mActualText;
};

#endif