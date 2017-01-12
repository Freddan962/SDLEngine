#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <string>

class State;

class StateManager
{
public:
	StateManager();

	void addState(State* state);
	void nextState();
	void prevState();

	State* getCurrentState();
	State* getNextState();
	State* getPrevState();

private:
	std::vector<State*> mStates;
	State* mCurrentState;
	int mCurrentStateIndex;
};

#endif