#include "Engine.h"
#include "game\MainState.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	Engine engine("Engine", 0.1);
	MainState st;
	engine.getStateManager()->addState(&st);
	engine.run();

	return 0;
}