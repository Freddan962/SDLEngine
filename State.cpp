#include "State.h"
#include <string>
#include "AssetContainer.h"
#include "Sprite.h"
#include "Engine.h"
#include "Physics.h"

State::State(Engine* engine, std::string name)
	: mAssets(new AssetContainer())
{
	mEngine = engine;
	mName = name;
}

void State::update() 
{ 
	updateSprites();
	checkForCollisions();
}

void State::render() 
{
	renderSprites();
}

void State::addSprite(std::shared_ptr<Sprite> sprite)
{
	mSprites.push_back(sprite);
}

void State::checkForCollisions()
{
	for (std::shared_ptr<Sprite> sprite : mSprites)
	{
		for (std::shared_ptr<Sprite> spriteInner : mSprites)
		{
			if (sprite.get() == spriteInner.get()) continue;

			if (Physics::isRectangularCollision(sprite->getBody().get(), spriteInner->getBody().get()))
			{
				sprite->onCollide(spriteInner.get());
				spriteInner->onCollide(sprite.get());
			}
		}
	}
		
}

void State::updateSprites()
{
	for (std::shared_ptr<Sprite> sprite : mSprites)
		sprite->update();
}

void State::renderSprites()
{
	for (std::shared_ptr<Sprite> sprite : mSprites)
		sprite->render(mEngine->getRenderer());
}

void State::handleEvent(SDL_Event* event) {}
void State::load() { }
void State::unload() { }