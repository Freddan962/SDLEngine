#include "MenuState.h"
#include "../Text.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../Centerer.h"
#include "../InputField.h"
#include "../StateManager.h"

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
	AssetLoader loader(mEngine->getRenderer(), "..\\SDLEngine\\source\\assets\\");
	mAssets->fonts.add("vertigo", loader.loadFont("vertigo.ttf", 40));
	mAssets->surfaces.add("buttonblue", loader.loadPNG( "buttonblue.png"));
	mAssets->surfaces.add("buttonblueinactive", loader.loadPNG("buttonblue_inactive.png"));
	mAssets->surfaces.add("background", loader.loadPNG("bg_purple.png"));
}

void MenuState::setUp() 
{
	mPlayer = std::dynamic_pointer_cast<Player>(savedSprites.get("player")->at(0));

	std::shared_ptr<Sprite> background(Sprite::getInstance(mAssets->surfaces.get("background"), mEngine->getRenderer()));
	background->scale(5, 5);
	sprites.add("background", background);

	std::shared_ptr<Text> welcomeTxt(new Text(mEngine->getRenderer()));
	welcomeTxt->setFont(mAssets->fonts.get("vertigo"));
	welcomeTxt->setText("Welcome, " + mPlayer->getName());
	Centerer::centerHorizontal(welcomeTxt.get(), mEngine->getSize()->x);
	welcomeTxt->getBody()->y = mEngine->getSize()->y * 0.3;
	mGUI.add("Welcome", welcomeTxt);

	std::shared_ptr<Button> playButton(Button::getInstance(mAssets->surfaces.get("buttonblueinactive"), mEngine->getRenderer()));
	Centerer::centerHorizontal(playButton.get(), mEngine->getSize()->x);
	playButton->getBody()->y = welcomeTxt->getBody()->y + welcomeTxt->getBody()->h + 20;
	playButton->text.setFont(mAssets->fonts.get("vertigo"));
	playButton->text.setText("Play");
	playButton->click = std::bind(&MenuState::playButtonClick, this);
	playButton->setSecondarySurface(mAssets->surfaces.get("buttonblue"));
	mPlayButton = playButton;
	mGUI.add("playbutton", playButton);

	std::shared_ptr<Button> exitButton(Button::getInstance(mAssets->surfaces.get("buttonblueinactive"), mEngine->getRenderer()));
	Centerer::centerHorizontal(exitButton.get(), mEngine->getSize()->x);
	exitButton->getBody()->y = playButton->getBody()->y + playButton->getBody()->h + 20;
	exitButton->text.setFont(mAssets->fonts.get("vertigo"));
	exitButton->text.setText("Exit");
	exitButton->click = std::bind(&MenuState::exitButtonClick, this);
	exitButton->setSecondarySurface(mAssets->surfaces.get("buttonblue"));
	mGUI.add("exitButton", exitButton);
}

void MenuState::playButtonClick()
{
	mEngine->getStateManager()->getNextState()->savedSprites.add("player", mPlayer);
	mEngine->getStateManager()->nextState();
}

void MenuState::exitButtonClick()
{
	mEngine->shutdown();
}

void MenuState::setPlayButtonText(std::string newText) 
{
	mPlayButton->text.setText(newText);
}