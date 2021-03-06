#include "Engine.h"
#include "pong/WelcomeState.h"
#include "pong/MenuState.h"
#include "pong/HighScoreState.h"
#include "pong/PlayState.h"
#include "pong/PhysicsState.h"
#include "StateManager.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	Engine engine("Pong Goal", 0, 1280, 860);
	engine.setFrameRate(60);

	WelcomeState welcomeState(&engine);
	engine.getStateManager()->addState(&welcomeState);

	MenuState menuState(&engine);
	engine.getStateManager()->addState(&menuState);

	PlayState playState(&engine);
	engine.getStateManager()->addState(&playState);

	PhysicsState physicsState(&engine);
	engine.getStateManager()->addState(&physicsState);

	engine.run();

	return 0;
}