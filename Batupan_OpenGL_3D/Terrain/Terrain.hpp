#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "../Loader/Loader.hpp"
#include "../Texture/ModelTexture.hpp"
#include "../Texture/TerrainTexturePack.hpp"

class Terrain
{
public:
	Terrain(const int& gridX, const int& gridZ, Loader& loader, const TerrainTexturePack& texturePack, const TerrainTexture& blendMap);

	// Getters
	inline BaseModel& GetBaseModel() { return m_model; }
	inline TerrainTexture& GetBlendMap() { return m_blendMap; }
	inline TerrainTexturePack& GetTexturePack() { return m_texturePack; }
	inline float& GetX() { return m_x; }
	inline float& GetZ() { return m_z; }
private:
	// Functions
	BaseModel GenerateTerrain(Loader& loader);

	const float SIZE = 800.0f;
	const int VERTEX_COUNT = 128;
	float m_x, m_z;
	TerrainTexture m_blendMap;
	TerrainTexturePack m_texturePack;
	BaseModel m_model;
};

#endif // !TERRAIN_HPP