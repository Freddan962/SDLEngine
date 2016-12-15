#include "Engine.h"
#include "pong/WelcomeState.h"
#include "pong/MenuState.h"
#include "pong/HighScoreState.h"
#include "pong/PlayState.h"
#include "StateManager.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	Engine engine("Pong Goal", 0, 1280, 860);
	engine.setFrameRate(60);

	//MainState st(&engine);
	//engine.getStateManager()->addState(&st);

	//MainMenuState mainMenuState(&engine);
	//engine.getStateManager()->addState(&mainMenuState);

	//PlayState playState(&engine);
	//engine.getStateManager()->addState(&playState);

	WelcomeState welcomeState(&engine);
	engine.getStateManager()->addState(&welcomeState);

	MenuState menuState(&engine);
	engine.getStateManager()->addState(&menuState);

	PlayState playState(&engine);
	engine.getStateManager()->addState(&playState);

	engine.run();

	return 0;
}