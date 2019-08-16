#include "../pch.h"
#include "Terrain.hpp"


Terrain::Terrain(const int& gridX, const int& gridZ, Loader& loader, const std::string& heightMap, const TerrainTexturePack& texturePack, const TerrainTexture& blendMap)
	: m_model(GenerateTerrain(loader, heightMap)), m_texturePack(texturePack), m_blendMap(blendMap)
{
	m_x = gridX * SIZE;
	m_z = gridZ * SIZE;

	m_startX = m_x;
	m_startZ = m_z;

	m_endX = m_startX + SIZE;
	m_endZ = m_startZ + SIZE;
}

const float Terrain::GetHeightOfTerrain(float worldX, float worldZ)
{
	float terrainX = worldX - m_x;
	float terrainZ = worldZ - m_z;
	float gridSquareSize = SIZE / ((float)m_heights.size() - 1);
	int gridX = (int)floor(terrainX / gridSquareSize);
	int gridZ = (int)floor(terrainZ / gridSquareSize);

	if (gridX >= m_heights.size() - 1 || gridZ >= m_heights.size() - 1 || gridX < 0 || gridZ < 0)
	{
		return 0;
	}

	float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
	assert(xCoord >= 0.0);
	assert(xCoord <= 1.0);
	assert(zCoord >= 0.0);
	assert(zCoord <= 1.0);

	float answer;
	glm::vec3 topLeft(0.0f, m_heights[gridX][gridZ], 0.0f);
	glm::vec3 topRight(1.0f, m_heights[gridX + 1][gridZ], 0.0f);
	glm::vec3 bottomLeft(0.0f, m_heights[gridX][gridZ + 1], 1.0f);
	glm::vec3 bottomRight(1.0f, m_heights[gridX + 1][gridZ + 1], 1.0f);
	glm::vec2 pos(xCoord, zCoord);

	if (xCoord <= (1 - zCoord))
	{
		answer = Maths::BarryCentric(topLeft, topRight, bottomLeft, pos);
	}
	else
	{
		answer = Maths::BarryCentric(topRight, bottomRight, bottomLeft, pos);
	}
	return answer;
}

BaseModel Terrain::GenerateTerrain(Loader& loader, const std::string& heightMap)
{
	std::cout << "Staring to generating of Terrain" << std::endl;
	clock_t startTime = clock();

	Image image(heightMap);

	int VERTEX_COUNT = image.GetHeight();

	int count = VERTEX_COUNT * VERTEX_COUNT;

	std::vector<glm::vec3> vertices(count), normals(count);
	std::vector<glm::vec2> textureCoords(count);
	std::vector<int> indices(6 * (VERTEX_COUNT - 1) * VERTEX_COUNT);


	m_heights = std::vector<std::vector<float>>(VERTEX_COUNT, std::vector<float>(VERTEX_COUNT));

	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			float height = GetHeight(j, i, image);
			m_heights.at(j).at(i) = height;

			vertices[vertexPointer] = glm::vec3(
				(float)j / ((float)VERTEX_COUNT - 1) * SIZE,
				height,
				(float)i / ((float)VERTEX_COUNT - 1) * SIZE);
			normals[vertexPointer] = CalculateNormal(j, i, image);
			textureCoords[vertexPointer] = glm::vec2(
				(float)j / ((float)VERTEX_COUNT - 1),
				(float)i / ((float)VERTEX_COUNT - 1));
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	// Print the time
	std::printf("Load time: %dms\n", clock() - startTime);

	return loader.LoadToVAO(vertices, textureCoords, normals, indices);
}

const glm::vec3 Terrain::CalculateNormal(int x, int z, Image& image)
{
	float heightL = GetHeight(x - 1, z, image);
	float heightR = GetHeight(x + 1, z, image);
	float heightD = GetHeight(x, z - 1, image);
	float heightU = GetHeight(x, z + 1, image);

	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);

	return normal;
}

const float Terrain::GetHeight(int x, int z, Image& image)
{
	if (x< 0 || x > image.GetHeight() || z < 0 || z >= image.GetWidth())
	{
		return 0;
	}

	float height = image.GetRGB(x, z);
	height += (MAX_PIXEL_COLOR / 2.0f);
	height /= (MAX_PIXEL_COLOR / 2.0f);
	height *= MAX_HEIGHT;

	return height;
}
