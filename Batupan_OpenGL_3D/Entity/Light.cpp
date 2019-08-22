#include "../pch.h"
#include "Light.hpp"


Light::Light(const glm::vec3& position, const glm::vec3& color)
{
	m_position = position;
	m_color = color;
	m_attenuation = glm::vec3(1.0f, 0.0f, 0.0f);
}

Light::Light(const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation)
{
	m_position = position;
	m_color = color;
	m_attenuation = attenuation;
}

const void Light::SetColor(const glm::vec3& color)
{
	m_color = color;
}

const void Light::SetPosition(const glm::vec3& position)
{
	m_position = position;
}

const void Light::SetAttenuation(const glm::vec3& attenuation)
{
	m_attenuation = attenuation;
}
