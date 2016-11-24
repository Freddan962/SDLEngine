#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include <memory>

#include "State.h"
#include "Vector2f.h"

class StateManager;

class Engine
{
public:
	Engine(std::string name, double version, float width, float height);
	~Engine();

	void run();
	void handleEvent(SDL_Event* event);

	void setFrameRate(int fps);

	int getFrameRate();
	std::shared_ptr<StateManager> getStateManager();
	SDL_Renderer* getRenderer();
	Vector2f* getSize();

private:
	void shutdown();

private:
	std::string mName;
	double mVersion;
	Vector2f mSize;

	int mFps;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mRunning;

	std::shared_ptr<StateManager> mStateManager;
};

#endif