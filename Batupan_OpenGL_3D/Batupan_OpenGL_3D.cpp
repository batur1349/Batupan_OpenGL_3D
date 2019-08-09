#include "pch.h"
#include "Engine/Engine.hpp"

int main()
{
#if _DEBUG
	// It is for checking if there is any memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Engine engine;

	engine.Run();

	return 0;
}