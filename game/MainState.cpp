#include "MainState.h"
#include "../Engine.h"
#include "../ImageLoader.h"
#include "../AssetContainer.h"
#include "../EntitySprite.h"
#include "../Physics.h"
#include "../AnimatedSprite.h"


void MainState::update() 
{
	State::update();

	//std::cout << "Updating MainState" << std::endl;
}

void MainState::render()
{
	State::render();
	//std::cout << "Rendering MainState" << std::endl;
}

void MainState::handleEvent(SDL_Event* event)
{
	//std::cout << "Handling event MainState" << std::endl;
}

void MainState::load()
{
	//std::cout << "Loading MainState" << std::endl;
	ImageLoader loader(mEngine->getRenderer());
	mAssets.get()->addTexture("buff", loader.loadBMP("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\iconbuff.bmp"));
	mAssets.get()->addTexture("door1", loader.loadPNG("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\door1.png"));
	mAssets.get()->addTexture("door2", loader.loadPNG("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\door2.png"));
	mAssets.get()->addTexture("door3", loader.loadPNG("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\door3.png"));
	mAssets.get()->addTexture("door4", loader.loadPNG("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\door4.png"));

	std::shared_ptr<EntitySprite> sprite(new EntitySprite(mAssets.get()->getTexture("buff")));
	sprite->getBody()->h = 50;
	sprite->getBody()->w = 50;
	sprite->setSpeed((float)100 / mEngine->getFrameRate(), 0);

	std::shared_ptr<EntitySprite> spriteRight(new EntitySprite(mAssets.get()->getTexture("buff")));
	spriteRight->getBody()->h = 50;
	spriteRight->getBody()->w = 50;
	spriteRight->getBody()->x = mEngine->getSize()->x - spriteRight->getBody()->w;
	spriteRight->setSpeed((float)100 / mEngine->getFrameRate() * -1, 0);

	box1 = sprite;
	box2 = spriteRight;

	addSprite(sprite);
	addSprite(spriteRight);

	//AnimatedSprite
	std::shared_ptr<AnimatedSprite> animated(new AnimatedSprite(mAssets->getTexture("door1")));
	animated->addFrame(mAssets->getTexture("door2"));
	animated->addFrame(mAssets->getTexture("door3"));
	animated->addFrame(mAssets->getTexture("door4"));
	animated->getBody()->h = 24;
	animated->getBody()->w = 24;
	animated->getBody()->x = 300;
	animated->getBody()->y = 250;

	addSprite(animated);
}

void MainState::unload()
{
	std::cout << "Unloading MainState" << std::endl;
}

