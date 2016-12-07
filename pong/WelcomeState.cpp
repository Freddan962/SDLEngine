#include "WelcomeState.h"
#include "../Text.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"

void WelcomeState::update()
{
	State::update();
}

void WelcomeState::render()
{
	State::render();
}

void WelcomeState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
}

void WelcomeState::load()
{
	State::load();
	loadAssets();
	setUp();
}

void WelcomeState::unload()
{
	State::unload();
}

void WelcomeState::loadAssets() {
	std::string assetPath = "..\\engine\\source\\assets\\";
	AssetLoader loader(mEngine->getRenderer());
	mAssets->fonts.add("vertigo", loader.loadFont(assetPath + "vertigo.ttf", 40));
}

void WelcomeState::setUp() {
	std::shared_ptr<Text> welcomeTxt(new Text(mEngine->getRenderer()));
	welcomeTxt->setFont(mAssets->fonts.get("vertigo"));
	welcomeTxt->setText("Enter name");
	mGUI.add("Welcome", welcomeTxt);
}