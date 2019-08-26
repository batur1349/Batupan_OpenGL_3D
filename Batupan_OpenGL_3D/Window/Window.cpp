#include "../pch.h"
#include "Window.hpp"
#include "../Renderer/MasterRenderer.hpp"


Window::Window(const int& width, const int& height, const std::string& title)
{
	// Set the windows title
	m_title = title;

	// Get the aspect ratio of window
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	// Set minimum OpenGL version and options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, GLFW_DONT_CARE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create the OpenGL window with GLFW
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	// Check if window was created
	if (m_window != NULL)
	{
		std::cout << "Window created successfully" << std::endl;

		// Set OpenGL context to the window, it is needed for the GLEW initialization
		glfwMakeContextCurrent(m_window);

		// Set OpenGL Window Resize Event
		glfwSetWindowSizeCallback(m_window, MasterRenderer::WindowResizeEvent);

		// Set OpenGL viewport to full size of the window
		glViewport(0, 0, width, height);

		// Enable vertical sync
		glfwSwapInterval(0);
	}
	else
	{
		// Check if GLFW is not initialized yet
		if (GLFW_NOT_INITIALIZED)
		{
			std::cerr << "ERROR: GLFW is not initialized!" << std::endl;
		}
		else
		{
			std::cerr << "ERROR: Failed to create window" << std::endl;
		}
	}
}

Window::~Window()
{
	std::cout << "Window destroyed" << std::endl;
	glfwDestroyWindow(m_window);
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window::Update()
{
	// Update the FPS counter
	//ShowFps();

	// Tell GLFW to swap buffers so the old frame will be removed and new frame will be displayed
	glfwSwapBuffers(m_window);

	// Tell GLFW to get window events so we can pull the window, interect with mouse and keyboard so on
	glfwPollEvents();
}

void Window::ShowFps()
{
	// Initialized for once and this will be size of the fps counter array
	const static int SIZE = 1200;

	// Array of doubles to count the current fps ratio
	// And initialize it with zeros
	static double avgList[SIZE] = { 0.0 };

	// Variables to computer frame render time
	static double previous = 0.0;
	double now = glfwGetTime();
	double average = 0.0;

	// Change the values in the array
	for (unsigned int i = 0; i < SIZE - 1; i++)
	{
		avgList[i] = avgList[i + 1];
		average += avgList[i];
	}

	// Store the new time in the last slot
	avgList[SIZE - 1] = now - previous;

	// Add the new time to the average
	average += avgList[SIZE - 1];

	// Divide average my the array size to get the average time
	average /= SIZE;

	// Update the title with the FPS
	glfwSetWindowTitle(m_window, (m_title + " | FPS: " + std::to_string(1.0f / average) + " | MS: " + m_msTitle).c_str());

	// Store the current time
	previous = now;
}

void Window::ShowFps(const bool& windowTitle)
{
	// Initialized for once and this will be size of the fps counter array
	const static int SIZE = 1200;

	// Array of doubles to count the current fps ratio
	// And initialize it with zeros
	static double avgList[SIZE] = { 0.0 };

	// Variables to computer frame render time
	static double previous = 0.0;
	double now = glfwGetTime();
	double average = 0.0;

	// Change the values in the array
	for (unsigned int i = 0; i < SIZE - 1; i++)
	{
		avgList[i] = avgList[i + 1];
		average += avgList[i];
	}

	// Store the new time in the last slot
	avgList[SIZE - 1] = now - previous;

	// Add the new time to the average
	average += avgList[SIZE - 1];

	// Divide average my the array size to get the average time
	average /= SIZE;

	// Update the title with the FPS
	if (windowTitle)
		glfwSetWindowTitle(m_window, (m_title + " | FPS: " + std::to_string(1.0f / average)).c_str());
	else
		std::cout << "Average FPS: " << std::to_string(1.0f / average) << "\n";

	// Store the current time
	previous = now;
}

const bool& Window::IsOpen()
{
	// If the close flag didn't issued to the window return the opposite of the closing state
	return !glfwWindowShouldClose(m_window);
}

float& Window::GetAspectRatio()
{
	return m_aspectRatio;
}

void Window::SetMsTitle(const std::string& msTitle)
{
	// Set the ms value to the title
	m_msTitle = msTitle;
}
