#include "../pch.h"
#include "WaterTile.hpp"


WaterTile::WaterTile(const float& centerX, const float& centerZ, const float& height, const float& tile)
{
	m_centerX = centerX;
	m_centerZ = centerZ;
	m_height = height;

	TILE_SIZE = tile;
}
