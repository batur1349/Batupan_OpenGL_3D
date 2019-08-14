#ifndef TERRAINTEXTUREPACK_HPP
#define TERRAINTEXTUREPACK_HPP

#include "TerrainTexture.hpp"

class TerrainTexturePack
{
public:
	TerrainTexturePack(const TerrainTexture& bgTexture, const TerrainTexture& rTexture, const TerrainTexture& gTexture, const TerrainTexture& bTexture);

	inline TerrainTexture& GetBackgroundTexture() { return m_backgroundTexture; }
	inline TerrainTexture& GetRedTexture() { return m_rTexture; }
	inline TerrainTexture& GetGreenTexture() { return m_gTexture; }
	inline TerrainTexture& GetBlueTexture() { return m_bTexture; }
private:
	TerrainTexture m_backgroundTexture, m_rTexture, m_gTexture, m_bTexture;
};

#endif // !TERRAINTEXTUREPACK_HPP