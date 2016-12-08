#include "MenuState.h"
#include "../Text.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../Centerer.h"
#include "../InputField.h"

void MenuState::update()
{
	State::update();
}

void MenuState::render()
{
	State::render();
}

void MenuState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
}

void MenuState::load()
{
	State::load();
	loadAssets();
	setUp();
}

void MenuState::unload()
{
	State::unload();
}

void MenuState::loadAssets() 
{
	std::string assetPath = "..\\engine\\source\\assets\\";
	AssetLoader loader(mEngine->getRenderer());
	mAssets->fonts.add("vertigo", loader.loadFont(assetPath + "vertigo.ttf", 40));
	mAssets->surfaces.add("buttonblue", loader.loadPNG(assetPath + "buttonblue.png"));
}

void MenuState::setUp() 
{
	mPlayer = std::dynamic_pointer_cast<Player>(savedSprites.get("player")->at(0));

	std::shared_ptr<Text> welcomeTxt(new Text(mEngine->getRenderer()));
	welcomeTxt->setFont(mAssets->fonts.get("vertigo"));
	welcomeTxt->setText("Welcome, " + mPlayer->getName());
	Centerer::centerHorizontal(welcomeTxt.get(), mEngine->getSize()->x);
	welcomeTxt->getBody()->y = mEngine->getSize()->y * 0.3;
	mGUI.add("Welcome", welcomeTxt);

	std::shared_ptr<Button> playButton(new Button(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(playButton.get(), mEngine->getSize()->x);
	playButton->getBody()->y = welcomeTxt->getBody()->y + welcomeTxt->getBody()->h + 20;
	playButton->text.setFont(mAssets->fonts.get("vertigo"));
	playButton->text.setText("Play");
	playButton->click = std::bind(&MenuState::playButtonClick, this);
	mGUI.add("playbutton", playButton);

	std::shared_ptr<Button> highScoreButton(new Button(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(highScoreButton.get(), mEngine->getSize()->x);
	highScoreButton->getBody()->y = playButton->getBody()->y + playButton->getBody()->h + 20;
	highScoreButton->text.setFont(mAssets->fonts.get("vertigo"));
	highScoreButton->text.setText("High Scores");
	highScoreButton->click = std::bind(&MenuState::highScoreButtonClick, this);
	mGUI.add("highScorebutton", highScoreButton);

	std::shared_ptr<Button> exitButton(new Button(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(exitButton.get(), mEngine->getSize()->x);
	exitButton->getBody()->y = highScoreButton->getBody()->y + highScoreButton->getBody()->h + 20;
	exitButton->text.setFont(mAssets->fonts.get("vertigo"));
	exitButton->text.setText("Exit");
	exitButton->click = std::bind(&MenuState::exitButtonClick, this);
	mGUI.add("exitButton", exitButton);
}

void MenuState::playButtonClick()
{

}

void MenuState::highScoreButtonClick()
{

}

void MenuState::exitButtonClick()
{
	mEngine->shutdown();
}