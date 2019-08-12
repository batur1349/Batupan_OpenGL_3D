#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "../Loader/Loader.hpp"
#include "../Texture/ModelTexture.hpp"

class Terrain
{
public:
	Terrain(const int& gridX, const int& gridZ, Loader& loader, const ModelTexture& texture);

	// Getters
	inline BaseModel& GetBaseModel() { return m_model; }
	inline ModelTexture& GetTexture() { return m_texture; }
	inline float& GetX() { return m_x; }
	inline float& GetZ() { return m_z; }
private:
	// Functions
	BaseModel GenerateTerrain(Loader& loader);

	const float SIZE = 800.0f;
	const int VERTEX_COUNT = 128;
	float m_x, m_z;
	ModelTexture m_texture;
	BaseModel m_model;
};

#endif // !TERRAIN_HPP