#include "StateManager.h"
#include "State.h"

StateManager::StateManager()
	: mCurrentStateIndex(-1)
{
	mCurrentState = nullptr;
}

void StateManager::addState(State* state)
{
	if (!mCurrentState)
	{
		mCurrentState = state;
		mCurrentStateIndex = 0;
		mCurrentState->load();
	}

	mStates.push_back(state);
}

void StateManager::nextState()
{
	if (mStates.size() - 1 < mCurrentStateIndex + 1) return;

	mCurrentState->unload();
	mCurrentStateIndex += 1;
	mCurrentState = mStates.at(mCurrentStateIndex);
	mCurrentState->load();
}

void StateManager::prevState()
{
	if (mCurrentStateIndex - 1 < 0) return;

	mCurrentState->unload();
	mCurrentStateIndex -= 1;
	mCurrentState = mStates.at(mCurrentStateIndex);
	mCurrentState->load();
}

State* StateManager::getCurrentState()
{
	return mCurrentState;
}