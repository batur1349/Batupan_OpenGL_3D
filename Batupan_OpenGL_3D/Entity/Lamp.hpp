#ifndef LAMP_HPP
#define LAMP_HPP

#include "Light.hpp"
#include "Entity.hpp"

class Lamp
{
public:
	Lamp(const std::string& name, Loader& loader, const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation);
	Lamp(const TexturedModel& entityModel, const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation);

	// Getters
	inline const Light& GetLight() const { return m_light; }
	inline const Entity& GetEntity() const { return m_entity; }
	inline const glm::vec3& GetEntityPosition() const { return m_entityPosition; }
	inline const glm::vec3& GetLightPosition() const { return m_lightPosition; }

	// Setters
	inline const void SetPosition(const glm::vec3& entityPosition) { m_entityPosition = entityPosition; m_lightPosition = entityPosition + glm::vec3(0.0f, 13.5f, 0.0f); }
	inline const void SetRotation(const glm::vec3& entityRotation) { m_entity.SetRotation(entityRotation); }
	inline const void SetScale(const glm::vec3& entityScale) { m_entity.SetScale(entityScale); }
private:
	Light m_light;
	Entity m_entity;
	glm::vec3 m_entityPosition, m_lightPosition;
};

#endif // !LAMP_HPP