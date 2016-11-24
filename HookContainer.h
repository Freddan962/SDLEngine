#ifndef HOOKCONTAINER_H
#define HOOKCONTAINER_H

#include "SDL.h"
#include <map>
#include <vector>

template <class T>
class HookContainer
{
public:
	template <class T>
	void addHook(T type, void(*func)())
	{
		if (mHooks.find(type) != mHooks.end())
			mHooks.at(type).push_back(func);
		else
		{
			std::vector<void(*)()> hooks;
			hooks.push_back(func);
			mHooks.insert(std::pair<T, std::vector<void(*)()>>(type, hooks));
		}
	}

	template <class T>
	void handleEvent(T event)
	{
		if (mHooks.find(event) != mHooks.end())
		{
			std::vector<void(*)()> hooks = mHooks.at(event);

			for (auto hook : hooks)
				hook();
		}
	}

private:
	std::map<T, std::vector<void(*)()>> mHooks;
};

#endif