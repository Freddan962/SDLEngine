#include "Engine.h"

Engine::Engine(std::string name, double version)
	: mName(name),
	mVersion(version),
	mRunning(true)
{
	mWindow = WindowBuilder::build(name + " " + std::to_string(mVersion), 640, 480);
	mRenderer = RenderBuilder::build(mWindow);

	if (!mWindow)
		shutdown();
}

Engine::~Engine() {}

void Engine::run()
{
	SDL_ShowWindow(mWindow);

	while (mRunning)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type) 
			{
			case SDL_QUIT: mRunning = false; break;
			case SDL_KEYDOWN: break;
			}
		}

		SDL_RenderClear(mRenderer);
		SDL_RenderPresent(mRenderer);
	}

	shutdown();
}

void Engine::shutdown()
{
	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);

	if (mWindow)
		SDL_DestroyWindow(mWindow);

	SDL_Quit();
}