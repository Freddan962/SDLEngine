#include "MainMenuState.h"
#include "../Engine.h"
#include "../Button.h"
#include "../AssetContainer.h"
#include "../AssetLoader.h"
#include "../Centerer.h"
#include "../StateManager.h"
#include "../AnimatedSprite.h"
#include "../Sound.h"
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
	mAssets->surfaces.add("logo", loader.loadPNG(assetPath + "logo.png")); //iCCP complain cause

	mAssets->surfaces.add("buttonblue", loader.loadPNG(assetPath + "buttonblue.png"));

	mAssets->surfaces.add("bgblack", loader.loadPNG(assetPath + "bgblack.png"));
	mAssets->surfaces.add("bgblue", loader.loadPNG(assetPath + "bgblue.png"));
	mAssets->surfaces.add("bgdarkpurple", loader.loadPNG(assetPath + "bgdarkpurple.png"));
	mAssets->surfaces.add("bgpurple", loader.loadPNG(assetPath + "bgpurple.png"));

	mAssets->chunks.add("theme", loader.loadOGG(assetPath + "theme.ogg"));

	mAssets->fonts.add("vertigo", loader.loadFont(assetPath + "vertigo.ttf", 40));
	
	}

void MainMenuState::prepareButtons()
{
	std::shared_ptr<Button> playButton(new Button(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(playButton.get(), mEngine->getSize()->x);
	playButton->getBody()->y = 330;
	playButton->click = std::bind(&StateManager::nextState, mEngine->getStateManager());
	playButton->text.setFont(mAssets->fonts.get("vertigo"));
	playButton->text.setText("P l a y");

	std::shared_ptr<Button> exitButton(new Button(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(exitButton.get(), mEngine->getSize()->x);
	exitButton->getBody()->y = 400;
	exitButton->click = std::bind(&Engine::shutdown, mEngine);
	exitButton->text.setFont(mAssets->fonts.get("vertigo"));
	exitButton->text.setText("E x i t");;

	std::shared_ptr<AnimatedSprite> background(new AnimatedSprite(mAssets->surfaces.get("bgblack"), mEngine->getRenderer()));
	background->addFrame(mAssets->surfaces.get("bgblue"));
	background->addFrame(mAssets->surfaces.get("bgdarkpurple"));
	background->addFrame(mAssets->surfaces.get("bgpurple"));
	background->setAnimationSpeed(150);
	background->getBody()->y = -1;
	background->getBody()->h = mEngine->getSize()->y + 1;
	background->getBody()->w = mEngine->getSize()->x;

	std::shared_ptr<Sprite> logo(new Sprite(mAssets->surfaces.get("logo"), mEngine->getRenderer()));
	logo->getBody()->h = 200;
	logo->getBody()->w = 333;
	Centerer::centerHorizontal(logo.get(), mEngine->getSize()->x);
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