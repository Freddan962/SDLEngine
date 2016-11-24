#include "Engine.h"
#include "game\MainState.h"
#include "StateManager.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	Engine engine("Engine", 0.1);
	engine.setFrameRate(60);

	MainState st(&engine);
	engine.getStateManager()->addState(&st);

	engine.run();

	return 0;
}