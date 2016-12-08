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
	void setCutLimit(int limit);
	void setInputLimit(int limit);

	std::string getText();
	int getCutLimit();
	int getInputLimit();

private:
	void cut();
	bool shouldCut(std::string text);
	void updateText(std::string text);

private:
	int mInputLimit;
	int mCutLimit;
	std::string mActualText;
};

#endif