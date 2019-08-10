#include "../pch.h"
#include "Camera.hpp"


Camera::Camera()
{
	m_position = glm::vec3(0.0f);
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
}

const void Camera::Move()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W))
	{
		m_position.z -= 0.02f;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S))
	{
		m_position.z += 0.02f;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D))
	{
		m_position.x += 0.02f;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A))
	{
		m_position.x -= 0.02f;
	}
}
