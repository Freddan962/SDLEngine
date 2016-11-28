#include "MainMenuState.h"
#include "../Engine.h"
#include "../Button.h"
#include "../AssetContainer.h"
#include "../ImageLoader.h"
#include "../SpriteCenterer.h"
#include "../StateManager.h"
#include "../AnimatedSprite.h"
#include "../SoundLoader.h"
#include "../Sound.h";

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
	State::load();

	loadAssets();
	prepareButtons();
	prepare();
}

void MainMenuState::unload()
{
	State::unload();
}

void MainMenuState::loadAssets()
{
	std::string assetPath = "..\\engine\\source\\assets\\";
	ImageLoader loader(mEngine->getRenderer());
	mAssets->addTexture("logo", loader.loadPNG(assetPath + "logo.png")); //iCCP complain cause

	mAssets->addTexture("exitButton", loader.loadPNG(assetPath + "exitbutton.png"));
	mAssets->addTexture("playButton", loader.loadPNG(assetPath + "playbutton.png"));

	mAssets->addTexture("bgblack", loader.loadPNG(assetPath + "bgblack.png"));
	mAssets->addTexture("bgblue", loader.loadPNG(assetPath + "bgblue.png"));
	mAssets->addTexture("bgdarkpurple", loader.loadPNG(assetPath + "bgdarkpurple.png"));
	mAssets->addTexture("bgpurple", loader.loadPNG(assetPath + "bgpurple.png"));

	SoundLoader soundLoader;
	mAssets->addChunk("theme", soundLoader.loadOGG(assetPath + "theme.ogg"));
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

	std::shared_ptr<Sprite> logo(new Sprite(mAssets->getTexture("logo")));
	logo->getBody()->h = 200;
	logo->getBody()->w = 333;
	SpriteCenterer::centerHorizontal(logo.get(), mEngine->getSize()->x);
	logo->getBody()->y = 50;
	
	mGUI.add("logo", logo);
	mGUI.add("playButton", playButton);
	mGUI.add("exitButton", exitButton);
	sprites.add("backkground", background);
}

void MainMenuState::prepare()
{
	std::shared_ptr<Sound> theme(new Sound(mAssets->getChunk("theme")));
	theme->repeat();
	theme->play();
	sounds.add("theme", theme);
}