#include "../pch.h"
#include "Engine.hpp"


Engine::Engine()
{
	// Initialized GLFW
	if (glfwInit())
	{
		// Print the GLFW success
		std::cout << "GLFW initialized successfully" << std::endl;

		// Create the display manager (pointers must be deleted)
		m_window = new Window(960, 540, "Barbaros OpenGL 3D Engine");

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

	// TERRAIN TEXTURE //

	TerrainTexture bgTexture(loader.LoadTexture2D("grassTerrain"));
	TerrainTexture rTexture(loader.LoadTexture2D("dirtTerrain"));
	TerrainTexture gTexture(loader.LoadTexture2D("grassFlowersTerrain"));
	TerrainTexture bTexture(loader.LoadTexture2D("pathTerrain"));
	TerrainTexturePack texturePack(bgTexture, rTexture, gTexture, bTexture);
	TerrainTexture blendMap(loader.LoadTexture2D("blendMap"));

	// TERRAIN TEXTURE //

	BaseModel treeModel = OBJFileLoader::LoadAssimpObjFile("tree", loader);
	ModelTexture treeModelTexture = loader.LoadTexture2D("tree");
	TexturedModel treeTexturedModel(treeModel, treeModelTexture);
	BaseModel fernModel = OBJFileLoader::LoadAssimpObjFile("fern", loader);
	ModelTexture fernModelTexture = loader.LoadTexture2D("fern");
	fernModelTexture.SetTransparency(true);
	TexturedModel fernTexturedModel(fernModel, fernModelTexture);
	BaseModel grassModel = OBJFileLoader::LoadAssimpObjFile("grass", loader);
	ModelTexture grassModelTexture = loader.LoadTexture2D("grass");
	grassModelTexture.SetTransparency(true); grassModelTexture.SetFakeLightning(true);
	TexturedModel grassTexturedModel(grassModel, grassModelTexture);

	BaseModel playerModel = OBJFileLoader::LoadAssimpObjFile("player", loader);
	ModelTexture playerTexture = loader.LoadTexture2D("player");
	TexturedModel playerTexturedModel(playerModel, playerTexture);
	Player player(playerTexturedModel, glm::vec3(0.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(0.75f));

	Terrain terrain(0, 0, loader, "heightMap", texturePack, blendMap);
	Light light(glm::vec3(20000.0f, 20000.0f, 2000.0f), glm::vec3(1.0f));
	Camera camera(&player);
	MasterRenderer renderer;

	std::vector<Entity> entities;
	float LO = 0, HI = 800;
	for (size_t i = 0; i < 200; i++)
	{
		float rX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		float rZ = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		float ry = terrain.GetHeightOfTerrain(rX, rZ);
		entities.emplace_back(treeTexturedModel, glm::vec3(rX, ry, rZ), glm::vec3(0.0f), glm::vec3(5.0f));
		rX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		rZ = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		ry = terrain.GetHeightOfTerrain(rX, rZ);
		entities.emplace_back(fernTexturedModel, glm::vec3(rX, ry, rZ), glm::vec3(0.0f), glm::vec3(1.0f));
		rX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		rZ = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		ry = terrain.GetHeightOfTerrain(rX, rZ);
		entities.emplace_back(grassTexturedModel, glm::vec3(rX, ry, rZ), glm::vec3(0.0f), glm::vec3(1.0f));
	}

	m_lastFrame = glfwGetTime();
	while (m_window->IsOpen())
	{
		// Update the deltaTime 
		UpdateDeltatime();

		// Update the game
		camera.Update();
		player.Update(m_deltaTime, terrain);

		renderer.ConstructTerrain(terrain);
		renderer.ConstructEntity(player);
		for (auto& entity : entities)
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
