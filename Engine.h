#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include <string>

#include "WindowBuilder.h"
#include "RenderBuilder.h"

class Engine
{
public:
	Engine(std::string name, double version);
	~Engine();

	void run();

private:
	void shutdown();

private:
	std::string mName;
	double mVersion;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mRunning;
};

#endif