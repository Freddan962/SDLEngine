#ifndef HOOKCONTAINER_H
#define HOOKCONTAINER_H

#include "SDL.h"
#include <map>
#include <vector>
#include <functional>

typedef std::function<void()> Func;

template <class T, class Y = SDL_EventType>
class HookContainer
{
public:
	void addHook(T type, Func func)
	{
		if (mHooks.find(type) != mHooks.end())
			mHooks.at(type).push_back(func);
		else
		{
			std::vector<Func> hooks;
			hooks.push_back(func);
			mHooks.insert(std::pair<T, std::vector<Func>>(type, hooks));
		}
	}

	void addHook(T type, Func func, Y condition)
	{
		if (mConditionHooks.find(type) != mConditionHooks.end())
		{
			mConditionHooks.at(type).push_back(std::pair<Func, Y>(func, condition));
		}
		else
		{
			std::vector<std::pair<Func, Y>> hooks;
			hooks.push_back((std::pair<Func, Y>(func, condition)));
			mConditionHooks.insert(std::pair<T, std::vector<std::pair<Func, Y>>>(type, hooks));
		}
	}

	void handleEvent(T event, SDL_Event* eventSt = nullptr)
	{
		if (mHooks.find(event) != mHooks.end())
		{
			std::vector<Func> hooks = mHooks.at(event);

			for (auto hook : hooks)
				hook();
		}

		if (!eventSt) return;
		if (mConditionHooks.find(event) != mConditionHooks.end())
		{
			std::vector<std::pair<Func, Y>> hooks = mConditionHooks.at(event);

			for (std::pair<Func, Y> hook : hooks)
				if (eventSt->type == hook.second)
					hook.first();
		}
	}

private:
	std::map<T, std::vector<Func>> mHooks;
	std::map<T, std::vector<std::pair<Func, Y>>> mConditionHooks;
};

#endif