#include "PlayLogic.h"
#include "../State.h"
#include "Player.h"
#include <memory>
#include <iostream>

PlayLogic::PlayLogic(State* state)
{
	mState = state;
}

void PlayLogic::update()
{

}

void PlayLogic::render(SDL_Renderer * renderer)
{

}

void PlayLogic::playerShoot()
{
	std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(mState->getSprites("player")->at(0));
	player->fire();
}
