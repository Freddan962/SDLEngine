#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include <memory>

#include "State.h"

class StateManager;

class Engine
{
public:
	Engine(std::string name, double version);
	~Engine();

	void run();
	void setFrameRate(int fps);
	int getFrameRate();

	std::shared_ptr<StateManager> getStateManager();
	SDL_Renderer* getRenderer();

private:
	void shutdown();

private:
	std::string mName;
	double mVersion;

	int mFps;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mRunning;

	std::shared_ptr<StateManager> mStateManager;
};

#endif