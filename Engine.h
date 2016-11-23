#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include <string>

#include "WindowBuilder.h"
#include "RenderBuilder.h"
#include "StateManager.h"

class Engine
{
public:
	Engine(std::string name, double version);
	~Engine();

	void run();
	StateManager* getStateManager();

private:
	void shutdown();

private:
	std::string mName;
	double mVersion;

	const int FPS = 60;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mRunning;

	StateManager mStateManager;
};

#endif