#include "pch.h"
#include "Window/Window.hpp"

int main()
{
#if _DEBUG
	// It is for checking if there is any memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	glfwInit();
	Window window(800, 600, "First Window!");
	while (window.IsOpen())
	{
		// Event
		window.Update();

		// Update

		// Render
	}

	return 0;
}