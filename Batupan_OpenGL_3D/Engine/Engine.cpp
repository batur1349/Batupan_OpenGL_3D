#include "../pch.h"
#include "Engine.hpp"
#include "../Gui/GuiTexture.hpp"
#include "../Gui/GuiRenderer.hpp"
#include "../Toolbox/MousePicker.hpp"
#include "../Water/WaterShader.hpp"
#include "../Water/WaterRenderer.hpp"
#include "../Water/WaterFrameBuffers.hpp"

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

	BaseModel treeModel = OBJFileLoader::LoadAssimpObjFile("lowPolyTree", loader);
	ModelTexture treeModelTexture = loader.LoadTexture2D("lowPolyTree");
	TexturedModel treeTexturedModel(treeModel, treeModelTexture);
	BaseModel fernModel = OBJFileLoader::LoadAssimpObjFile("fern", loader);
	ModelTexture fernTextureAtlas = loader.LoadTexture2D("fernAtlas");
	fernTextureAtlas.SetTransparency(true);
	fernTextureAtlas.SetNumberOfRows(2);
	TexturedModel fernTexturedModel(fernModel, fernTextureAtlas);

	BaseModel grassModel = OBJFileLoader::LoadAssimpObjFile("oneGrass", loader);
	ModelTexture grassTextureAtlas = loader.LoadTexture2D("flowersAtlas");
	grassTextureAtlas.SetTransparency(true);
	grassTextureAtlas.SetFakeLightning(true);
	grassTextureAtlas.SetNumberOfColumns(4);
	grassTextureAtlas.SetNumberOfRows(2);
	TexturedModel grassTexturedModel(grassModel, grassTextureAtlas);

	BaseModel playerModel = OBJFileLoader::LoadAssimpObjFile("player", loader);
	ModelTexture playerTexture = loader.LoadTexture2D("player");
	TexturedModel playerTexturedModel(playerModel, playerTexture);
	Player player(playerTexturedModel, glm::vec3(247.0f, 8.58f, 259.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(0.75f));

	std::vector<Terrain> terrains;
	terrains.push_back(Terrain(0, 0, loader, "heightMap", texturePack, blendMap));
	Camera camera(&player);
	MasterRenderer renderer(loader);

	std::vector<GuiTexture> guis;
	guis.push_back(GuiTexture(loader.LoadTexture2D("baturpanLogo"), glm::vec2(0.75f, 0.75f), glm::vec2(0.25f)));
	GuiRenderer guiRenderer(loader);

	std::vector<Entity> entities;
	float LO = 0, HI = 800;
	int count;
#ifdef _DEBUG
	count = 50;
#else
	count = 600;
#endif // _DEBUG

	for (size_t i = 0; i < count; i++)
	{
		float rX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		float rZ = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		float rY = terrains.at(0).GetHeightOfTerrain(rX, rZ);
		int randomIndex = rand() % 4;
		int randomFlower = rand() % 8;
		if (rY > 0.0f)
			entities.emplace_back(treeTexturedModel, glm::vec3(rX, rY, rZ), glm::vec3(0.0f), glm::vec3(0.75f));
		rX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		rZ = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		rY = terrains.at(0).GetHeightOfTerrain(rX, rZ);
		if (rY > 0.0f)
			entities.emplace_back(fernTexturedModel, randomIndex, glm::vec3(rX, rY, rZ), glm::vec3(0.0f), glm::vec3(1.0f));
		rX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		rZ = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		rY = terrains.at(0).GetHeightOfTerrain(rX, rZ);
		if (rY > 0.0f)
			entities.emplace_back(grassTexturedModel, randomFlower, glm::vec3(rX, rY, rZ), glm::vec3(0.0f), glm::vec3(2.0f));
	}

	BaseModel lampModel = OBJFileLoader::LoadAssimpObjFile("lamp", loader);
	ModelTexture lampTexture = loader.LoadTexture2D("lamp");
	lampTexture.SetFakeLightning(true);
	TexturedModel lampTexturedModel(lampModel, lampTexture);
	std::vector<Lamp> lamps;
	float pY = terrains.at(0).GetHeightOfTerrain(247.0f, 249.0f);
	if (pY > 0.0f)
		lamps.push_back(Lamp(lampTexturedModel, glm::vec3(247.0f, pY, 249.0f), glm::vec3(1.0f), glm::vec3(0.75f, 0.005f, 0.0008f)));
	pY = terrains.at(0).GetHeightOfTerrain(207.0f, 364.0f);
	if (pY > 0.0f)
		lamps.push_back(Lamp(lampTexturedModel, glm::vec3(207.0f, pY, 364.0f), glm::vec3(1.0f), glm::vec3(0.75f, 0.005f, 0.0008f)));
	pY = terrains.at(0).GetHeightOfTerrain(217.0f, 536.0f);
	if (pY > 0.0f)
		lamps.push_back(Lamp(lampTexturedModel, glm::vec3(217.0f, pY, 536.0f), glm::vec3(1.0f), glm::vec3(0.75f, 0.005f, 0.0008f)));

	WaterFrameBuffers fbos;
	WaterShader waterShader;
	WaterRenderer waterRenderer(loader, waterShader, renderer.GetProjectionMatrix(), fbos);
	std::vector<WaterTile> waters;
	waters.push_back(WaterTile(400, 400, 0, 400));

	glm::vec3 terrainPoint;
	MousePicker picker(&camera, renderer.GetProjectionMatrix(), terrains);

	static double limitFPS = 1.0 / 60.0;
	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;

	m_lastFrame = glfwGetTime();
	while (m_window->IsOpen())
	{
		// - Measure time
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

		// - Only update at 60 frames / s
		while (deltaTime >= 1.0)
		{
			// Update Game Logic
			UpdateDeltatime();
			camera.Update();
			player.Update(m_deltaTime, terrains);
			if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT))
			{
				picker.Update();
				glm::vec3 terrainPoint = picker.GetCurrentTerrainPoint();
				if (terrainPoint != glm::vec3(0, 0, 0))
				{
					lamps.at(0).SetPosition(terrainPoint);
				}
			}

			updates++;
			deltaTime--;
		}

		// Render Game
		glEnable(GL_CLIP_DISTANCE0);

		// Render reflection texture
		fbos.BindReflectionFrameBuffer();
		float distance = 2 * (camera.GetPosition().y - waters.at(0).GetHeight());
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - distance, camera.GetPosition().z));
		camera.InvertPitch();
		renderer.RenderScene(entities, terrains, lamps, camera, m_deltaTime, glm::vec4(0, 1, 0, -waters.at(0).GetHeight()));
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + distance, camera.GetPosition().z));
		camera.InvertPitch();

		// Render refraction texture
		fbos.BindRefractionFrameBuffer();
		renderer.RenderScene(entities, terrains, lamps, camera, m_deltaTime, glm::vec4(0, -1, 0, waters.at(0).GetHeight()));

		// Render screen
		glDisable(GL_CLIP_DISTANCE0);
		fbos.UnbindCurrentFrameBuffer();
		renderer.ConstructEntity(player);
		renderer.RenderScene(entities, terrains, lamps, camera, m_deltaTime, glm::vec4(0, -1, 0, 15.0f));
		waterRenderer.Render(waters, camera, m_deltaTime);
		guiRenderer.Render(guis);
		frames++;

		// Update the window
		m_window->Update();

		// - Reset after one second
		if (glfwGetTime() - timer > 1.0)
		{
			timer++;
			std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
			updates = 0, frames = 0;
		}

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
