#include "MainState.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../EntitySprite.h"
#include "../Physics.h"
#include "../AnimatedSprite.h"
#include "../Button.h"

void MainState::update() 
{
	State::update();

	//std::cout << "Updating MainState" << std::endl;
}

void MainState::render()
{
	State::render();
	std::cout << "Rendering MainState" << std::endl;
}

void MainState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
	std::cout << "Handling event MainState" << std::endl;
}

void onClick()
{
	std::cout << "CLICKED" << std::endl;
}

void aClick()
{
	std::cout << "A CLICK" << std::endl;
}

void buttonClick()
{
	std::cout << "A BUTTON CLICK" << std::endl;
}

void MainState::load()
{
	std::string assetPath = "..\\engine\\source\\assets\\";
	AssetLoader loader(mEngine->getRenderer());

	mAssets->textures.add("buff", loader.loadBMP(assetPath + "iconbuff.bmp"));
	mAssets->textures.add("door1", loader.loadPNG(assetPath + "door1.png"));
	mAssets->textures.add("door2", loader.loadPNG(assetPath + "door2.png"));
	mAssets->textures.add("door3", loader.loadPNG(assetPath +  "door3.png"));
	mAssets->textures.add("door4", loader.loadPNG(assetPath +  "door4.png"));

	std::shared_ptr<EntitySprite> sprite(new EntitySprite(mAssets->textures.get("buff")));
	sprite->getBody()->h = 50;
	sprite->getBody()->w = 50;
	sprite->setSpeed((float)100 / mEngine->getFrameRate(), 0);

	std::shared_ptr<EntitySprite> spriteRight(new EntitySprite(mAssets->textures.get("buff")));
	spriteRight->getBody()->h = 50;
	spriteRight->getBody()->w = 50;
	spriteRight->getBody()->x = mEngine->getSize()->x - spriteRight->getBody()->w;
	spriteRight->setSpeed((float)100 / mEngine->getFrameRate() * -1, 0);

	box1 = sprite;
	box2 = spriteRight;

	sprites.add("sprite", sprite);
	sprites.add("spriteRight", spriteRight);

	//AnimatedSprite
	std::shared_ptr<AnimatedSprite> animated(new AnimatedSprite(mAssets->textures.get("door1")));
	animated->addFrame(mAssets->textures.get("door2"));
	animated->addFrame(mAssets->textures.get("door3"));
	animated->addFrame(mAssets->textures.get("door4"));
	animated->getBody()->h = 24;
	animated->getBody()->w = 24;
	animated->getBody()->x = 300;
	animated->getBody()->y = 250;

	sprites.add("animated", animated);

	std::shared_ptr<InputField> inputField(new InputField(mAssets->textures.get("door1"), mEngine->getRenderer()));
	inputField->getBody()->h = 80;
	inputField->getBody()->w = 80;
	inputField->getBody()->x = 400;
	inputField->getBody()->y = 300;
	inputField->setText("Welcome");
	inputField->setFontSize(70);
	mGUI.add("input", inputField);

	std::shared_ptr<Button> button(new Button(mAssets->textures.get("door1")));
	button->getBody()->h = 20;
	button->getBody()->w = 20;
	button->getBody()->x = 500;
	button->getBody()->y = 400;
	button->click = &buttonClick;
	mGUI.add("play", button);

	mKeyHooks.addHook(SDLK_a, std::bind(&Test::sumAndPrint, mTest.get(), 15, 20));
	mKeyHooks.addHook(SDLK_a, std::bind(&Test::sumAndPrint2, mTest.get()));
	mKeyHooks.addHook(SDLK_a, std::function<void()>(aClick));
	mEventHooks.addHook(SDL_MOUSEBUTTONUP, &onClick);
}

void MainState::unload()
{
	std::cout << "Unloading MainState" << std::endl;
}


