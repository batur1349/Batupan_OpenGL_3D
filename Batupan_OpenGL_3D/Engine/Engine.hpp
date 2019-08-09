#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../Window/Window.hpp"
#include "../Loader/Loader.hpp"
#include "../Renderer/Renderer.hpp"

class Engine
{
public:
	// Constructor & ~Destructor
	Engine();
	~Engine();
	// Functions
	void Run();

	// Getters
	const float& GetDeltaTime() const;
private:
	// Functions
	void UpdateDeltatime();
	// Variables
	float m_deltaTime;
	float m_lastFrame;
	Window* m_window;
};

#endif // !ENGINE_HPP