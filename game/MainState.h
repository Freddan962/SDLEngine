#ifndef MAINSTATE_H
#define MAINSTATE_H

#include <iostream>

class MainState : public State
{
public:
	MainState() : State("MainState") {}
	void update() { std::cout << "UPDATED" << std::endl;  }
	void handleEvent(SDL_Event* event) { std::cout << "HANDLED EVENT" << std::endl; }
	void render() { std::cout << "RENDERING" << std::endl; }
};

#endif