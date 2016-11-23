#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <string>

#include "State.h"

class StateManager
{
public:
	StateManager();

	void addState(State state);
	void nextState();
	void prevState();

	State* getCurrentState();

private:
	std::vector<State> mStates;
	State* mCurrentState;
	int mCurrentStateIndex;
};

#endif