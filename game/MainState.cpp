#include "MainState.h"
#include "../Engine.h"
#include "../ImageLoader.h"
#include "../AssetContainer.h"
#include "../Sprite.h"


void MainState::update() 
{
	State::update();
	std::cout << "Updating MainState" << std::endl;
}

void MainState::render()
{
	State::render();
	std::cout << "Rendering MainState" << std::endl;
	//SDL_RenderCopy(mEngine->getRenderer(), mAssets.get()->getTexture("buff"), NULL, NULL);
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
	std::shared_ptr<Sprite> sprite(new Sprite(mAssets.get()->getTexture("buff")));
	addSprite(sprite);
}

void MainState::unload()
{
	std::cout << "Unloading MainState" << std::endl;
}

