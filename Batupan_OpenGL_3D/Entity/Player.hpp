#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity
{
public:
	Player(const TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

	// Functions
	const void Update(const float& dt);
private:
	const void UpdateInput(const float& dt);

	// Variables
	TexturedModel m_texturedModel;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	bool m_jumped;
	float m_currentSpeed = 0.0f, m_currentTurnSpeed = 0.0f, m_upwardsSpeed = 0.0f;
	static const float RUN_SPEED, TURN_SPEED, JUMP_POWER, TERRAIN_HEIGHT, GRAVITY;
};

#endif // !PLAYER_HPP