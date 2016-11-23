#include "StateManager.h"

StateManager::StateManager()
	: mCurrentStateIndex(-1)
{
	mCurrentState = nullptr;
}

void StateManager::addState(State state)
{
	if (!mCurrentState)
	{
		mCurrentState = &state;
		mCurrentStateIndex = 0;
	}

	mStates.push_back(state);
}

void StateManager::nextState()
{
	if (mStates.size() - 1 < mCurrentStateIndex + 1) return;

	mCurrentStateIndex += 1;
	mCurrentState = &mStates.at(mCurrentStateIndex);
}

void StateManager::prevState()
{
	if (mCurrentStateIndex - 1 < 0) return;

	mCurrentStateIndex -= 1;
	mCurrentState = &mStates.at(mCurrentStateIndex);
}

State* StateManager::getCurrentState()
{
	return mCurrentState;
}