#ifndef TERRAINRENDERER_HPP
#define TERRAINRENDERER_HPP

#include "../Shader/TerrainShader.hpp"
#include "../Terrain/Terrain.hpp"

class TerrainRenderer
{
public:
	// Constructor and ~Destructor
	TerrainRenderer(TerrainShader& shader, const glm::mat4& projectionMatrix);

	// Functions
	const void Render(std::vector<Terrain>& terrains);
private:
	// Functions
	void PrepareTerrain(Terrain& terrain);
	void UnbindTexturedModel();
	void LoadModelMatrix(Terrain& terrain);

	// Variables
	TerrainShader& m_shader;
};

#endif // !TERRAINRENDERER_HPP