#include "State.h"
#include "AssetContainer.h"
#include <string>

State::State(Engine* engine, std::string name)
	: mAssets(new AssetContainer())
{
	mEngine = engine;
	mName = name;
}

void State::update() { }
void State::handleEvent(SDL_Event* event) {}
void State::render() { }
void State::load() { }
void State::unload() { }