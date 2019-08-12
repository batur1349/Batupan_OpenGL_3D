#include "../pch.h"
#include "Camera.hpp"


Camera::Camera()
{
	m_position = glm::vec3(0.0f, 5.0f, 0.0f);
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
}

const void Camera::Update()
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
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT))
	{
		m_position.y += 0.02f;
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_CONTROL))
	{
		m_position.y -= 0.02f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F6))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F7))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
