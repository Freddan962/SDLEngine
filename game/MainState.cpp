#include "MainState.h"

void MainState::update() 
{
	std::cout << "Updating" << std::endl;
}

void MainState::render()
{
	std::cout << "Rendering" << std::endl;
}

void MainState::handleEvent(SDL_Event* event)
{
	std::cout << "Handling event" << std::endl;
}

void MainState::load()
{
	std::cout << "Loading" << std::endl;
}

void MainState::unload()
{
	std::cout << "Unloading" << std::endl;
}

