#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Shader/BasicShader.hpp"
#include "EntityRenderer.hpp"
#include "TerrainRenderer.hpp"
#include "../Entity/Lamp.hpp"
#include "../Skybox/SkyboxRenderer.hpp"

class MasterRenderer
{
public:
	MasterRenderer(Loader& loader);

	inline const void Prepare() const;
	inline const static void EnableCulling();
	const static void DisableCulling();

	const void Render(const std::vector<Light>& lights, Camera& camera);
	inline const void ConstructEntity(Entity& entity);
	inline const void ConstructTerrain(Terrain& terrain) { m_terrains.push_back(terrain); }
	const void RenderLamps(std::vector<Lamp>& lamps, Camera& camera);
	const void RenderScene(const std::vector<Entity>& entities, const std::vector<Terrain>& terrains,
		const std::vector<Lamp>& lamps, Camera& camera, const float& dt);

	inline glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
	static void WindowResizeEvent(GLFWwindow* window, int width, int height);

	const static float FOV, NEAR_PLANE, FAR_PLANE; glm::mat4 m_projectionMatrix;
	const static float RED, GREEN, BLUE;
private:
	const glm::mat4& CreateProjectionMatrix();

	Frustum m_frustum;
	BasicShader m_entityShader; TerrainShader m_terrainShader;
	EntityRenderer m_entityRenderer; TerrainRenderer m_terrainRenderer;
	SkyboxRenderer m_skyboxRenderer;
	static bool m_projectionMatrix_Changed;

	// Containers
	std::vector<Terrain> m_terrains;
	std::map<TexturedModel, std::vector<Entity>, TextureModelCompare> m_entities;
};

#endif // !MASTERRENDERER_HPP