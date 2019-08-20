#include "../pch.h"
#include "Lamp.hpp"


Lamp::Lamp(const TexturedModel& entityModel, const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation)
	: m_light(Light(glm::vec3(position.x, position.y + 13.5f, position.z), color, attenuation)),
	m_entity(Entity(entityModel, position, glm::vec3(0.0f), glm::vec3(1.0f)))
{
	m_entityPosition = position;
	m_lightPosition = position + glm::vec3(0.0f, 13.5f, 0.0f);
}
