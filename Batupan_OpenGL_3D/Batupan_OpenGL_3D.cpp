#include "pch.h"
#include "Window/Window.hpp"
#include "Loader/Loader.hpp"
#include "Renderer/Renderer.hpp"

int main()
{
#if _DEBUG
	// It is for checking if there is any memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	glfwInit();
	glewExperimental = GL_TRUE;
	Window window(800, 600, "First Window!");
	glewInit();

	Loader loader;
	Renderer renderer;

	// OpenGL needs counter clockwise
	float vertices[] = {
	   -0.5f, 0.5f, 0.f,
	   -0.5f, -0.5f, 0.f,
	   0.5f, -0.5f, 0.f,
	   0.5f, -0.5f, 0.f,
	   0.5f, 0.5f, 0.f,
	   -0.5f, 0.5f, 0.f
	};

	int numberOfVertices = sizeof(vertices) / sizeof(vertices[0]);
	BaseModel* model = loader.LoadToVAO(vertices, numberOfVertices);

	while (window.IsOpen())
	{
		// Event
		renderer.Prepare();

		// Update

		// Render
		renderer.Render(model);
		window.Update();
	}

	glfwTerminate();
	delete model;
	return 0;
}