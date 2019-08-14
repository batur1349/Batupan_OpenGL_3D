#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../Window/Window.hpp"
#include "../Loader/Loader.hpp"
#include "../Renderer/EntityRenderer.hpp"
#include "../Shader/BasicShader.hpp"
#include "../Texture/ModelTexture.hpp"
#include "../Model/TexturedModel.hpp"
#include "../Loader/OBJFileLoader.hpp"
#include "../Entity/Light.hpp"
#include "../Renderer/MasterRenderer.hpp"
#include "../Entity/Player.hpp"

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
	float m_deltaTime = 0.0f;
	float m_lastFrame = 0.0f;
	Window* m_window = nullptr;
};

#endif // !ENGINE_HPP