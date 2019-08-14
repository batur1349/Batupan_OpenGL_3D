#include "../pch.h"
#include "TerrainTexturePack.hpp"


TerrainTexturePack::TerrainTexturePack(const TerrainTexture& bgTexture, const TerrainTexture& rTexture, const TerrainTexture& gTexture, const TerrainTexture& bTexture)
	:m_backgroundTexture(bgTexture), m_rTexture(rTexture), m_gTexture(gTexture), m_bTexture(bTexture)
{

}
