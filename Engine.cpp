#include "Engine.h"
#include "WindowBuilder.h"
#include "RenderBuilder.h"
#include "StateManager.h"
#include "sdl\include\SDL_mixer.h"

Engine::Engine(std::string name, double version, float width, float height)
	: mName(name),
	mVersion(version),
	mRunning(true),
	mStateManager(new StateManager())
{
	mSize.x = width;
	mSize.y = height;
	mWindow = WindowBuilder::build(name, mSize.x, mSize.y);
	mRenderer = RenderBuilder::build(mWindow);

	if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0)
		shutdown();

	if (TTF_Init() == -1)
		shutdown();

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
			handleEvent(&event);
			mStateManager->getCurrentState()->handleEvent(&event);
		}

		delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);

		//Update
		mStateManager->getCurrentState()->update();

		//Render
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
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

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();

	mRunning = false;
}

void Engine::setFrameRate(int fps)
{
	mFps = fps;
}

int Engine::getFrameRate()
{
	return mFps;
}

Vector2<int>* Engine::getSize()
{
	return &mSize;
}

void Engine::handleEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_QUIT: mRunning = false; break;
	}
}