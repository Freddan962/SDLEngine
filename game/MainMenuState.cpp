#include "MainMenuState.h"
#include "../Engine.h"
#include "../Button.h"
#include "../AssetContainer.h"
#include "../ImageLoader.h"
#include "../SpriteCenterer.h"
#include "../StateManager.h"
#include "../AnimatedSprite.h"

void MainMenuState::update()
{
	State::update();
}

void MainMenuState::render()
{
	State::render();
}

void MainMenuState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
}

void MainMenuState::load()
{
	loadAssets();
	prepareButtons();
}

void MainMenuState::unload()
{

}

void MainMenuState::loadAssets()
{
	ImageLoader loader(mEngine->getRenderer());
	mAssets->addTexture("exitButton", loader.loadPNG("..\\engine\\source\\assets\\exitbutton.png"));
	mAssets->addTexture("playButton", loader.loadPNG("..\\engine\\source\\assets\\playbutton.png"));

	mAssets->addTexture("bgblack", loader.loadPNG("..\\engine\\source\\assets\\bgblack.png"));
	mAssets->addTexture("bgblue", loader.loadPNG("..\\engine\\source\\assets\\bgblue.png"));
	mAssets->addTexture("bgdarkpurple", loader.loadPNG("..\\engine\\source\\assets\\bgdarkpurple.png"));
	mAssets->addTexture("bgpurple", loader.loadPNG("..\\engine\\source\\assets\\bgpurple.png"));
}

void MainMenuState::prepareButtons()
{
	std::shared_ptr<Button> playButton(new Button(mAssets->getTexture("playButton")));
	SpriteCenterer::centerHorizontal(playButton.get(), mEngine->getSize()->x);
	playButton->getBody()->y = 330;
	playButton->click = std::bind(&StateManager::nextState, mEngine->getStateManager());

	std::shared_ptr<Button> exitButton(new Button(mAssets->getTexture("exitButton")));
	SpriteCenterer::centerHorizontal(exitButton.get(), mEngine->getSize()->x);
	exitButton->getBody()->y = 400;
	exitButton->click = std::bind(&Engine::shutdown, mEngine);

	std::shared_ptr<AnimatedSprite> background(new AnimatedSprite(mAssets->getTexture("bgblack")));
	background->addFrame(mAssets->getTexture("bgblue"));
	background->addFrame(mAssets->getTexture("bgdarkpurple"));
	background->addFrame(mAssets->getTexture("bgpurple"));
	background->setAnimationSpeed(150);
	background->getBody()->y = -1;
	background->getBody()->h = mEngine->getSize()->y + 1;
	background->getBody()->w = mEngine->getSize()->x;

	mGUI.add("playButton", playButton);
	mGUI.add("exitButton", exitButton);
	addSprite("backkground", background);
}