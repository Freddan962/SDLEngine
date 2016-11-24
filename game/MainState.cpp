#include "MainState.h"
#include "../Engine.h"
#include "../ImageLoader.h"
#include "../AssetContainer.h"
#include "../EntitySprite.h"


void MainState::update() 
{
	State::update();
	std::cout << "Updating MainState" << std::endl;
}

void MainState::render()
{
	State::render();
	std::cout << "Rendering MainState" << std::endl;
}

void MainState::handleEvent(SDL_Event* event)
{
	std::cout << "Handling event MainState" << std::endl;
}

void MainState::load()
{
	std::cout << "Loading MainState" << std::endl;
	ImageLoader loader(mEngine->getRenderer());
	mAssets.get()->addTexture("buff", loader.loadBMP("C:\\Users\\Freddan962\\Desktop\\C++\\Lek\\Engine\\Engine\\Source\\assets\\iconbuff.bmp"));
	
	std::shared_ptr<EntitySprite> sprite(new EntitySprite(mAssets.get()->getTexture("buff")));
	sprite->getBody()->h = 50;
	sprite->getBody()->w = 50;
	sprite->setSpeed((float)100 / mEngine->getFrameRate(), 0);
	addSprite(sprite);
}

void MainState::unload()
{
	std::cout << "Unloading MainState" << std::endl;
}

