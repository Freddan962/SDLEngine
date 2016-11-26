#include "State.h"
#include <string>
#include "AssetContainer.h"
#include "Sprite.h"
#include "Engine.h"
#include "Physics.h"
#include "GUI.h"

State::State(Engine* engine, std::string name)
	: mAssets(new AssetContainer())
{
	mEngine = engine;
	mName = name;
}

void State::update() 
{ 
	mGUI.update();
	updateSprites();
	checkForCollisions();
}

void State::render() 
{
	renderSprites();
	mGUI.render(mEngine->getRenderer());
}

void State::addSprite(std::string name, std::shared_ptr<Sprite> sprite)
{
	if (mSprites.find(name) != mSprites.end())
	{
		mSprites.at(name).push_back(sprite);
	}
	else
	{
		std::vector<std::shared_ptr<Sprite>> sprites;
		sprites.push_back(sprite);
		mSprites.insert(std::pair<std::string, std::vector<std::shared_ptr<Sprite>>>(name, sprites));
	}
}

void State::checkForCollisions()
{
	for (std::shared_ptr<Sprite> sprite : getSprites())
	{
		for (std::shared_ptr<Sprite> spriteInner : getSprites())
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
	for (std::shared_ptr<Sprite> sprite : getSprites())
		sprite->update();
}

void State::renderSprites()
{
	for (std::shared_ptr<Sprite> sprite : getSprites())
		sprite->render(mEngine->getRenderer());
}

void State::handleEvent(SDL_Event* event) 
{
	mGUI.handleEvent(event);
	mKeyHooks.handleEvent(event->key.keysym.sym, event);
	mEventHooks.handleEvent((SDL_EventType)event->type);
}

std::vector<std::shared_ptr<Sprite>> State::getSprites()
{
	std::vector<std::shared_ptr<Sprite>> sprites;

	for (auto pair : mSprites)
	{
		std::vector<std::shared_ptr<Sprite>> pairSprites = pair.second;

		for (auto sprite : pairSprites)
			sprites.push_back(sprite);
	}

	return sprites;
}

std::vector<std::shared_ptr<Sprite>>* State::getSprites(std::string name)
{
	if (mSprites.find(name) != mSprites.end())
		return &mSprites.at(name);

	return nullptr;
}

void State::load() { }
void State::unload() { }