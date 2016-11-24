#include "State.h"
#include <string>
#include "AssetContainer.h"
#include "Sprite.h"
#include "Engine.h"

State::State(Engine* engine, std::string name)
	: mAssets(new AssetContainer())
{
	mEngine = engine;
	mName = name;
}

void State::update() 
{ 
	for (std::shared_ptr<Sprite> sprite : mSprites)
		sprite->update();
}

void State::render() 
{
	for (std::shared_ptr<Sprite> sprite : mSprites)
		sprite->render(mEngine->getRenderer());
}

void State::addSprite(std::shared_ptr<Sprite> sprite)
{
	mSprites.push_back(sprite);
}

void State::handleEvent(SDL_Event* event) {}
void State::load() { }
void State::unload() { }