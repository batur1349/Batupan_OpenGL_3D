#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "../Loader/Loader.hpp"
#include "../Texture/ModelTexture.hpp"
#include "../Texture/TerrainTexturePack.hpp"
#include "../Toolbox/Maths.hpp"

constexpr int VERTEX_COUNT = 128;
constexpr float SIZE = 800;
constexpr float MAX_HEIGHT = 60;
constexpr float MAX_PIXEL_COLOR = 256 * 256 * 256;

class Image
{
public:
	Image(const std::string& fileName)
	{
		// Load image data
		m_imageData = SOIL_load_image(("../Textures/" + fileName + ".png").c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGBA);
	}
	~Image()
	{
		SOIL_free_image_data(m_imageData);
	}

	unsigned long createRGB(int r, int g, int b)
	{
		return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	}

	inline int GetHeight() { return m_height; }
	inline int GetWidth() { return m_width; }

	inline float GetRGB(int x, int z)
	{
		long long int baseValue = -4294967296;
		long long int colorValue = 0;

		int r, g, b, a;
		r = static_cast<int>(m_imageData[(z * m_width + x) * 4 + 0]);
		g = static_cast<int>(m_imageData[(z * m_width + x) * 4 + 1]);
		b = static_cast<int>(m_imageData[(z * m_width + x) * 4 + 2]);
		a = static_cast<int>(m_imageData[(z * m_width + x) * 4 + 3]);

		std::stringstream stream, hexConvert;
		// FFFF FFFF AARR GGBB <---------- COLOR MEMORY PLACEMENT
		stream << std::hex << a;
		stream << std::hex << r;
		stream << std::hex << g;
		stream << std::hex << b;

		hexConvert << std::hex << stream.str();
		hexConvert >> colorValue;

		float returnValue = baseValue + colorValue;

		return returnValue;
	}
private:
	int m_width, m_height;
	unsigned char* m_imageData;
};

class Terrain
{
public:
	Terrain(const int& gridX, const int& gridZ, Loader& loader, const std::string& heightMap, const TerrainTexturePack& texturePack, const TerrainTexture& blendMap);

	// Getters
	inline BaseModel& GetBaseModel() { return m_model; }
	inline TerrainTexture& GetBlendMap() { return m_blendMap; }
	inline TerrainTexturePack& GetTexturePack() { return m_texturePack; }
	inline float& GetX() { return m_x; }
	inline float& GetZ() { return m_z; }
	inline float& GetStartX() { return m_startX; }
	inline float& GetStartZ() { return m_startZ; }
	inline float& GetEndX() { return m_endX; }
	inline float& GetEndZ() { return m_endZ; }

	const float GetHeightOfTerrain(float worldX, float worldZ);
private:
	// Functions
	std::vector<std::vector<float>> m_heights;
	BaseModel GenerateTerrain(Loader& loader, const std::string& heightMap);
	const glm::vec3 CalculateNormal(int x, int z, Image& image);
	const float GetHeight(int x, int z, Image& image);

	float m_x, m_z, m_startX, m_startZ, m_endX, m_endZ;
	TerrainTexture m_blendMap;
	TerrainTexturePack m_texturePack;
	BaseModel m_model;
};

#endif // !TERRAIN_HPP