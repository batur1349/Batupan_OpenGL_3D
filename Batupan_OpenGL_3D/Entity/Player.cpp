#include "../pch.h"
#include "Player.hpp"

const float Player::RUN_SPEED = 20.0f;
const float Player::TURN_SPEED = 160.0f;
const float Player::JUMP_POWER = 30.0f;
const float Player::TERRAIN_HEIGHT = 0.0f;
const float Player::GRAVITY = -50.0f;

Player::Player(const TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_texturedModel(model), m_position(position), m_rotation(rotation), m_scale(scale), Entity(model, position, rotation, scale)
{
}

const void Player::Update(const float& dt)
{
	// Update the keyboard of player
	UpdateInput(dt);

	// Rotate the player
	Rotate(glm::vec3(0.0f, m_currentTurnSpeed * dt, 0.0f));

	// Move the player
	float distance = m_currentSpeed * dt;
	float dx = distance * std::sin(GetRotation().y * static_cast<float>(static_cast<float>(3.1415) / static_cast <float>(180)));
	float dz = distance * std::cos(GetRotation().y * static_cast<float>(static_cast<float>(3.1415) / static_cast <float>(180)));
	Move(glm::vec3(dx, 0, dz));

	// Check the jump
	m_upwardsSpeed += GRAVITY * dt;
	Move(glm::vec3(0, m_upwardsSpeed * dt, 0));

	if (GetPosition().y < TERRAIN_HEIGHT)
	{
		m_upwardsSpeed = 0.0f;
		SetPosition(glm::vec3(GetPosition().x, TERRAIN_HEIGHT, GetPosition().z));
		m_jumped = false;
	}
}

const void Player::UpdateInput(const float& dt)
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W))
	{
		m_currentSpeed = -RUN_SPEED;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S))
	{
		m_currentSpeed = RUN_SPEED;
	}
	else
	{
		m_currentSpeed = 0.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D))
	{
		m_currentTurnSpeed = -TURN_SPEED;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A))
	{
		m_currentTurnSpeed = TURN_SPEED;
	}
	else
	{
		m_currentTurnSpeed = 0.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) && m_jumped == false)
	{
		m_upwardsSpeed = JUMP_POWER;
		m_jumped = true;
	}
}
