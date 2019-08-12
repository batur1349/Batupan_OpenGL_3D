#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Shader/BasicShader.hpp"
#include "EntityRenderer.hpp"
#include "TerrainRenderer.hpp"

class MasterRenderer
{
public:
	MasterRenderer();

	inline const void Prepare() const;
	void Render(Light& light, Camera& camera);
	void ConstructEntity(Entity& entity);
	inline const void ConstructTerrain(Terrain& terrain) { m_terrains.push_back(terrain); }

	inline glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
private:
	const glm::mat4& CreateProjectionMatrix();

	BasicShader m_entityShader; TerrainShader m_terrainShader;
	EntityRenderer m_entityRenderer; TerrainRenderer m_terrainRenderer;
	const static float FOV, NEAR_PLANE, FAR_PLANE; glm::mat4 m_projectionMatrix;
	// Container
	std::vector<Terrain> m_terrains;
	std::map<TexturedModel, std::vector<Entity>, TextureModelCompare> m_entities;
};

#endif // !MASTERRENDERER_HPP