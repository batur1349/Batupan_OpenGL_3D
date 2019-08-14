#include "../pch.h"
#include "Camera.hpp"


Camera::Camera()
{
	m_position = glm::vec3(-20.0f, 20.0f, -20.0f);
	m_pitch = 30.0f;
	m_yaw = 150.0f;
	m_roll = 0.0f;
}

const void Camera::Update()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Q))
	{
		m_yaw--;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E))
	{
		m_yaw++;
	}
}
