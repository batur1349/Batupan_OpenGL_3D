#include "../pch.h"
#include "Engine.hpp"
#include "../Shader/BasicShader.hpp"


Engine::Engine()
{
	// Initialized GLFW
	if (glfwInit())
	{
		// Print the GLFW success
		std::cout << "GLFW initialized successfully" << std::endl;

		// Create the display manager (pointers must be deleted)
		m_window = new Window(800, 600, "Barbaros OpenGL 3D Engine");

		// Initialize glew using experimental
		glewExperimental = true;
		GLenum status = glewInit();

		// Check if the GLEW has initialized
		if (status == GLEW_OK)
		{
			// Print the GLEW success
			std::cout << "GLEW initialized successfully" << std::endl;
		}
		else
		{
			// Print the GLEW didn't initialized properly
			std::cerr << "ERROR: GLEW failed to initialize \n" << glewGetErrorString(status) << std::endl;
		}
	}
	else
	{
		// Print the GLFW didn't initialized properly
		std::cerr << "ERROR: GLFW failed to initialize" << std::endl;
	}
}

Engine::~Engine()
{
	// Delete the window 
	delete m_window;
	// Cleanup the GLFW stuff
	glfwTerminate();
}

void Engine::Run()
{
	std::cout << "Engine::Run() loop is now running!" << "\n";

	Loader loader;
	Renderer renderer;
	BasicShader shader;
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

	m_lastFrame = glfwGetTime();
	while (m_window->IsOpen())
	{
		// Update the deltaTime 
		UpdateDeltatime();
		renderer.Prepare();

		// Update the game

		// Render the game
		shader.Start();
		renderer.Render(model);
		shader.Stop();
		renderer.Render(model2);

		// Update the window
		m_window->Update();

		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			m_window->Close();
	}

	delete model;
	delete model2;
}

const float& Engine::GetDeltaTime() const
{
	return m_deltaTime;
}

void Engine::UpdateDeltatime()
{
	// Calculate deltatime of current frame
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;

	// Update the window's ms title
	m_window->SetMsTitle(std::to_string(m_deltaTime * 1000.0f));
}
