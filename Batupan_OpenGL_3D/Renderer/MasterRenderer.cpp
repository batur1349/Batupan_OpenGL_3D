#include "../pch.h"
#include "MasterRenderer.hpp"

const float MasterRenderer::FOV = 60.0f;
const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000.0f;

const float MasterRenderer::RED = 0.5f;
const float MasterRenderer::GREEN = 0.5f;
const float MasterRenderer::BLUE = 0.5f;

bool MasterRenderer::m_projectionMatrix_Changed = false;

MasterRenderer::MasterRenderer()
	: m_entityRenderer(m_entityShader, CreateProjectionMatrix()), m_terrainRenderer(m_terrainShader, CreateProjectionMatrix())
{
	EnableCulling();
	glEnable(GL_DEPTH_TEST);
}

inline const void MasterRenderer::Prepare() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(RED, GREEN, BLUE, 1.0f);
}

inline const void MasterRenderer::EnableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

const void MasterRenderer::DisableCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::Render(Light& light, Camera& camera)
{
	// Prepare the screen
	Prepare();
	// Activate the shader
	m_entityShader.Start();
	// Check if projection matrix has changed and then load 
	if (m_projectionMatrix_Changed)
		m_entityShader.LoadProjectionMatrix(CreateProjectionMatrix());
	// Load the skyColor
	m_entityShader.LoadSkyColor(glm::vec3(RED, GREEN, BLUE));
	// Load shader parameters
	m_entityShader.LoadLight(light);
	m_entityShader.LoadViewMatrix(&camera);
	// Render all of the entities
	m_entityRenderer.RenderEntities(m_entities);
	// Deactivate shader and clear entities
	m_entityShader.Stop();
	// Start the terrain shader
	m_terrainShader.Start();
	// Check if projection matrix has changed and then load
	if (m_projectionMatrix_Changed)
	{
		m_terrainShader.LoadProjectionMatrix(m_projectionMatrix);
		m_projectionMatrix_Changed = false;
	}
	// Load the skyColor
	m_terrainShader.LoadSkyColor(glm::vec3(RED, GREEN, BLUE));
	// Load terrain shader parameters
	m_terrainShader.LoadLight(light);
	m_terrainShader.LoadViewMatrix(camera);
	// Render all of the terrains
	m_terrainRenderer.Render(m_terrains);
	// Stop terrain shader and clear terrains
	m_terrainShader.Stop();
	// Clear the terrains batch, for the memory management
	m_terrains.clear();
	// Clear the entities batch, for the memory management
	m_entities.clear();
}

void MasterRenderer::ConstructEntity(Entity& entity)
{
	// Get the textured model
	TexturedModel& texturedModel = entity.GetTexturedModel();
	// If the texturedmodel is in the map this will do nothing
	// If it is not in the map it will insert it
	m_entities.insert(std::make_pair(texturedModel, std::vector<Entity>()));
	// Add the entity to the entities list
	m_entities.find(texturedModel)->second.push_back(entity);
}

const glm::mat4& MasterRenderer::CreateProjectionMatrix()
{
	int sizeX, sizeY;
	glfwGetWindowSize(glfwGetCurrentContext(), &sizeX, &sizeY);

	GLfloat aspectRatio = (float)((float)sizeX / (float)sizeY);
	GLfloat angle = FOV / 2.0f;
	GLfloat radAngle = glm::radians(angle);
	GLfloat tanAngle = tanf(radAngle);
	GLfloat y_scale = (GLfloat)(1.0f / tanAngle) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustum_length = FAR_PLANE - NEAR_PLANE;

	m_projectionMatrix = glm::mat4(1.0f);

	m_projectionMatrix[0][0] = x_scale;
	m_projectionMatrix[1][1] = y_scale;
	m_projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	m_projectionMatrix[2][3] = -1;
	m_projectionMatrix[3][2] = -(2 * NEAR_PLANE * FAR_PLANE) / frustum_length;
	m_projectionMatrix[3][3] = 0;

	return m_projectionMatrix;
}

void MasterRenderer::WindowResizeEvent(GLFWwindow* window, int width, int height)
{
	m_projectionMatrix_Changed = true;
	glViewport(0, 0, width, height);
}
