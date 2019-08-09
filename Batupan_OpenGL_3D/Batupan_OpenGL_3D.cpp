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

	std::vector<GLfloat> vertices = {
		-0.5f, 0.5f, 0.0f,  // V0
		-0.5f, -0.5f, 0.0f, // V1
		0.5f, -0.5f, 0.0f,  // V2
		0.5f, 0.5f, 0.0f    // V3
	};
	std::vector<GLuint> indices = {
		0, 1, 3, // Top left triangle
		3, 1, 2  // Bottom right triangle
	};

	BaseModel* model = loader.LoadToVAO(vertices, indices);

	std::vector<GLfloat> verts = {
		-1.0f, 1.0f, 0.0f,  // V0
		-1.0f, 0.9f, 0.0f,  // V2
		-0.9f, 0.9f, 0.0f,    // V3
		-0.9f, 1.0f, 0.0f // V1
	};

	BaseModel* model2 = loader.LoadToVAO(verts, indices);

	while (window.IsOpen())
	{
		// Event
		renderer.Prepare();

		// Update

		// Render
		renderer.Render(model);
		renderer.Render(model2);
		window.Update();
	}

	glfwTerminate();
	delete model;
	delete model2;
	return 0;
}