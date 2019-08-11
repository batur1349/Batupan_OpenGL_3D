#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Model/TexturedModel.hpp"
#include "../Loader/OBJFileLoader.hpp"

class Entity
{
public:
	Entity(const std::string& entityName, Loader& loader, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));
	Entity(const TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

	// Methods
	const void Move(glm::vec3 moveVector);
	const void Move(float x, float y, float z);
	const void Rotate(glm::vec3 rotateVector);
	const void Rotate(float rx, float ry, float rz);

	// Getters
	inline TexturedModel& GetTexturedModel() { return m_texturedModel; }
	inline glm::vec3& GetPosition() { return m_position; }
	inline glm::vec3& GetRotation() { return m_rotation; }
	inline glm::vec3& GetScale() { return m_scale; }

	// Setters
	inline void SetPosition(glm::vec3 position) { m_position = position; }
	inline void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }
	inline void SetScale(glm::vec3 scale) { m_scale = scale; }
private:
	// Variables
	TexturedModel m_texturedModel;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

#endif // !ENTITY_HPP