#include "MainMenuState.h"
#include "../Engine.h"
#include "../Button.h"
#include "../AssetContainer.h"
#include "../AssetLoader.h"
#include "../SpriteCenterer.h"
#include "../StateManager.h"
#include "../AnimatedSprite.h"
#include "../Sound.h";
#include "../Text.h"

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
	AssetLoader loader(mEngine->getRenderer());
	mAssets->textures.add("logo", loader.loadPNG(assetPath + "logo.png")); //iCCP complain cause

	mAssets->textures.add("exitButton", loader.loadPNG(assetPath + "exitbutton.png"));
	mAssets->textures.add("playButton", loader.loadPNG(assetPath + "playbutton.png"));

	mAssets->textures.add("bgblack", loader.loadPNG(assetPath + "bgblack.png"));
	mAssets->textures.add("bgblue", loader.loadPNG(assetPath + "bgblue.png"));
	mAssets->textures.add("bgdarkpurple", loader.loadPNG(assetPath + "bgdarkpurple.png"));
	mAssets->textures.add("bgpurple", loader.loadPNG(assetPath + "bgpurple.png"));

	mAssets->chunks.add("theme", loader.loadOGG(assetPath + "theme.ogg"));

	mAssets->fonts.add("vertigo", loader.loadFont(assetPath + "vertigo.ttf", 24));
}

void MainMenuState::prepareButtons()
{
	std::shared_ptr<Button> playButton(new Button(mAssets->textures.get("playButton")));
	SpriteCenterer::centerHorizontal(playButton.get(), mEngine->getSize()->x);
	playButton->getBody()->y = 330;
	playButton->click = std::bind(&StateManager::nextState, mEngine->getStateManager());

	std::shared_ptr<Button> exitButton(new Button(mAssets->textures.get("exitButton")));
	SpriteCenterer::centerHorizontal(exitButton.get(), mEngine->getSize()->x);
	exitButton->getBody()->y = 400;
	exitButton->click = std::bind(&Engine::shutdown, mEngine);

	std::shared_ptr<AnimatedSprite> background(new AnimatedSprite(mAssets->textures.get("bgblack")));
	background->addFrame(mAssets->textures.get("bgblue"));
	background->addFrame(mAssets->textures.get("bgdarkpurple"));
	background->addFrame(mAssets->textures.get("bgpurple"));
	background->setAnimationSpeed(150);
	background->getBody()->y = -1;
	background->getBody()->h = mEngine->getSize()->y + 1;
	background->getBody()->w = mEngine->getSize()->x;

	std::shared_ptr<Sprite> logo(new Sprite(mAssets->textures.get("logo")));
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
	std::shared_ptr<Sound> theme(new Sound(mAssets->chunks.get("theme")));
	theme->repeat();
	theme->play();

	/*std::shared_ptr<Text> text(new Text(mEngine->getRenderer()));
	text->getBody()->x = 40;
	text->getBody()->y = 40;
	text->setFont(mAssets->fonts.get("vertigo"));
	text->setText("Lorem Ipsem");*/

	//mGUI.add("text", text);
}