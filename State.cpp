#include "State.h"

State::State(std::string name) 
{
	mName = name;
}

void State::update() { }
void State::handleEvent(SDL_Event* event) {}
void State::render() { }