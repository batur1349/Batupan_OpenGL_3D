#include "../pch.h"
#include "Entity.hpp"


Entity::Entity(const std::string& entityName, Loader& loader, const float& shineDamper, const float& reflectivity, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_texturedModel(OBJFileLoader::LoadAssimpObjFile(entityName, loader), loader.LoadTexture2D(entityName))
{
	SetShineDamper(shineDamper);
	SetReflectivity(reflectivity);

	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

Entity::Entity(const TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_texturedModel(model)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

Entity::Entity(const TexturedModel& model, const int& textureIndex, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_texturedModel(model)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	m_textureIndex = textureIndex;
}

const void Entity::Move(glm::vec3 moveVector)
{
	m_position += moveVector;
}

const void Entity::Move(float x, float y, float z)
{
	m_position += glm::vec3(x, y, z);
}

const void Entity::Rotate(glm::vec3 rotateVector)
{
	m_rotation += rotateVector;
}

const void Entity::Rotate(float rx, float ry, float rz)
{
	m_rotation += glm::vec3(rx, ry, rz);
}

const float Entity::GetTextureXOffset()
{
	int cols = m_texturedModel.GetModelTexture().GetNumberOfColumns();
	int column = m_textureIndex % cols;
	return (float)column / (float)cols;
}

const float Entity::GetTextureYOffset()
{
	int rows = m_texturedModel.GetModelTexture().GetNumberOfRows();
	int cols = m_texturedModel.GetModelTexture().GetNumberOfColumns();
	int row = m_textureIndex / cols;
	return (float)row / (float)rows;
}
