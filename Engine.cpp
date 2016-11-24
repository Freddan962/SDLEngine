#include "Engine.h"
#include "WindowBuilder.h"
#include "RenderBuilder.h"
#include "StateManager.h"


Engine::Engine(std::string name, double version, float width, float height)
	: mName(name),
	mVersion(version),
	mRunning(true),
	mStateManager(new StateManager())
{
	mSize.x = width;
	mSize.y = height;
	mWindow = WindowBuilder::build(name + " " + std::to_string(mVersion), mSize.x, mSize.y);
	mRenderer = RenderBuilder::build(mWindow);

	if (!mWindow)
		shutdown();
}

Engine::~Engine(){ }

void Engine::run()
{
	SDL_ShowWindow(mWindow);

	const int tickInterval = 1000 / mFps;
	Uint32 nextTick;
	int delay;

	while (mRunning)
	{
		nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			mStateManager->getCurrentState()->handleEvent(&event);

			switch (event.type) 
			{
			case SDL_QUIT: mRunning = false; break;
			case SDL_KEYDOWN: break;
			}
		}

		delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);

		//Update
		mStateManager->getCurrentState()->update();

		//Render
		SDL_RenderClear(mRenderer);
		mStateManager->getCurrentState()->render();
		SDL_RenderPresent(mRenderer);
	}

	shutdown();
}

std::shared_ptr<StateManager> Engine::getStateManager() { return mStateManager; }
SDL_Renderer* Engine::getRenderer() { return mRenderer; }

void Engine::shutdown()
{
	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);

	if (mWindow)
		SDL_DestroyWindow(mWindow);

	SDL_Quit();
}

void Engine::setFrameRate(int fps)
{
	mFps = fps;
}

int Engine::getFrameRate()
{
	return mFps;
}

Vector2f* Engine::getSize()
{
	return &mSize;
}