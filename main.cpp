#include "Engine.h"
#include "game\MainState.h"
#include "game\MainMenuState.h"
#include "game\PlayState.h"
#include "StateManager.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	Engine engine("Engine", 0.1, 640, 480);
	engine.setFrameRate(60);

	//MainState st(&engine);
	//engine.getStateManager()->addState(&st);

	MainMenuState mainMenuState(&engine);
	engine.getStateManager()->addState(&mainMenuState);

	PlayState playState(&engine);
	engine.getStateManager()->addState(&playState);

	engine.run();

	return 0;
}