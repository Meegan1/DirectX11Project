#include <windows.h>
#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	Engine *engine = new Engine(hInstance, nShowCmd);
	engine->Run();
	delete engine;

	return 0;
}

