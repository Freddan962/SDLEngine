#ifndef GUI_H
#define GUI_H

#include "SDL.h"
#include <map>
#include <memory>
#include <string>
#include "Vector2.h"

class InputField;
class Button;
class Sprite;

namespace GUI
{
	class GUI
	{
	public:
		GUI();

		void update();
		void render(SDL_Renderer* renderer);
		void handleEvent(SDL_Event* event);

		void add(std::string name, std::shared_ptr<InputField> field);
		void add(std::string name, std::shared_ptr<Button> button);
		void add(std::string name, std::shared_ptr<Sprite> sprite);
	
	private:
		void updateElements();
		void renderElements(SDL_Renderer* renderer);

		void handleMouseButtonDown(SDL_Event* event);
		void handleTextInput(SDL_Event* event);
		void handleElementInteraction(std::shared_ptr<SDL_Rect> click);
		void handleInputFieldInteraction(std::shared_ptr<SDL_Rect> click);
		std::shared_ptr<SDL_Rect> getMouseClick();

	private:
		std::map<std::string, std::shared_ptr<InputField>> mInputFields;
		std::map<std::string, std::shared_ptr<Button>> mButtons;
		std::map<std::string, std::shared_ptr<Sprite>> mSprites;
		std::map<std::string, std::shared_ptr<InputField>> mActiveInputFields;
		Vector2<int> mCursorSize;
	};
}

#endif