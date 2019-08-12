#include "../pch.h"
#include "Engine.hpp"
#include "../Loader/OBJFileLoader.hpp"
#include "../Entity/Light.hpp"
#include "../Renderer/MasterRenderer.hpp"


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

	Entity entity("stall", loader, 1.0f, 0.0f, glm::vec3(0, 0, -25), glm::vec3(0), glm::vec3(1));
	Light light(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(1.0f));

	Camera camera;

	MasterRenderer renderer;

	m_lastFrame = glfwGetTime();
	while (m_window->IsOpen())
	{
		// Update the deltaTime 
		UpdateDeltatime();

		// Update the game
		entity.Rotate(glm::vec3(0.0f, 0.3f, 0.0f));
		camera.Move();
		renderer.ConstructEntity(entity);
		renderer.Render(light, camera);

		// RenderEntities the game

		// Update the window
		m_window->Update();

		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			m_window->Close();
	}
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
