#ifndef WATERTILE_HPP
#define WATERTILE_HPP

class WaterTile
{
public:
	WaterTile(const float& centerX, const float& centerZ, const float& height, const float& tile = 60.0f);

	inline const float& GetCenterX() const { return m_centerX; }
	inline const float& GetCenterZ() const { return m_centerZ; }
	inline const float& GetHeight() const { return m_height; }
	inline const float& GetSize() const { return TILE_SIZE; }
private:
	float m_centerX, m_centerZ, m_height;
	float TILE_SIZE = 60;
};

#endif // !WATERTILE_HPP