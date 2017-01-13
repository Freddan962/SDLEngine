#include "State.h"
#include <string>
#include "AssetContainer.h"
#include "Sprite.h"
#include "Engine.h"
#include "Physics.h"
#include "GUI.h"
#include "Sound.h"
#include "EntitySprite.h"
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

void State::checkForCollisions()
{
	for (std::shared_ptr<Sprite> sprite : sprites.get())
	{
		for (std::shared_ptr<Sprite> spriteInner : sprites.get())
		{
			if (sprite.get() == spriteInner.get()) continue;

			if (Physics::isRectangularPixelCollision(sprite.get(), spriteInner.get())) 
			{
				sprite->onCollide(spriteInner.get());
				spriteInner->onCollide(sprite.get());
			} 
		}
	}	
}

void State::updateSprites()
{
	for (std::shared_ptr<Sprite> sprite : sprites.get())
		sprite->update();
}

void State::renderSprites()
{
	for (std::shared_ptr<Sprite> sprite : sprites.get())
		sprite->render();
}

void State::handleEvent(SDL_Event* event) 
{
	mGUI.handleEvent(event);
	mKeyHooks.handleEvent(event->key.keysym.sym, event);
	mEventHooks.handleEvent((SDL_EventType)event->type);
}


void State::load() { }

void State::unload()
{
	pauseAllSounds();
}

void State::pauseAllSounds()
{
	auto collection = sounds.get();
	for (std::vector<std::shared_ptr<Sound>>::iterator it = collection.begin(); it != collection.end(); it++)
		it->get()->pause();
}