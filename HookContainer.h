#ifndef HOOKCONTAINER_H
#define HOOKCONTAINER_H

#include "SDL.h"
#include <map>
#include <vector>
#include <functional>

typedef std::function<void()> Func;

template <class T>
class HookContainer
{
public:
	template <class T>
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

	template <class T>
	void handleEvent(T event)
	{
		if (mHooks.find(event) != mHooks.end())
		{
			std::vector<Func> hooks = mHooks.at(event);

			for (auto hook : hooks)
				hook();
		}
	}

private:
	std::map<T, std::vector<Func>> mHooks;
};

#endif