#include "stdafx.h"
#include "Engine.h"

int main(int argc, char *args[])
{
	Engine engine;
	if (engine.Initialize())
	{
		engine.Update();
	}
	engine.Shutdown();
	return 0;
}