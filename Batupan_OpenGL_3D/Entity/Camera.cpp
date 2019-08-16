#include "../pch.h"
#include "Camera.hpp"

int Camera::m_scrollY;

Camera::Camera(Player* player)
	: m_worldUP(0.0f, 1.0f, 0.0f)
{
	m_player = player;

	m_pitch = 20.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;

	m_scrollY = 0;

	m_front = glm::normalize(m_player->GetPosition());

	m_distanceFromPlayer = 50.0f;
	m_angleAroundThePlayer = 180.0f;

	glfwSetScrollCallback(glfwGetCurrentContext(), Scroll_Event);

	int windowX, windowY;
	glfwGetWindowSize(glfwGetCurrentContext(), &windowX, &windowY);
	glfwSetCursorPos(glfwGetCurrentContext(), windowX / 2.0f, windowY / 2.0f);
}

const void Camera::Update()
{
	UpdateInput();

	CalculateZoom();
	CalculatePitch();
	CalculateAngleAroundPlayer();
	CalculateCameraPosition(CalculateHorizontalDistance(), CalculateVerticalDistance());

	m_yaw = 180.0f - (m_player->GetRotation().y + m_angleAroundThePlayer);

	glfwGetCursorPos(glfwGetCurrentContext(), &m_lastMouseX, &m_lastMouseY);
}

const void Camera::UpdateInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R))
	{
		m_angleAroundThePlayer = 180.0f;
		m_pitch = 20.0f;
		m_distanceFromPlayer = 50.0;
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

const void Camera::CalculateZoom()
{
	m_distanceFromPlayer -= m_scrollY;

	if (m_distanceFromPlayer > 50.0f)
		m_distanceFromPlayer = 50.0f;
	else if (m_distanceFromPlayer < 20.0f)
		m_distanceFromPlayer = 20.0f;

	m_scrollY = 0;
}

const void Camera::CalculatePitch()
{
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT))
	{
		double posY;
		glfwGetCursorPos(glfwGetCurrentContext(), NULL, &posY);

		float pitchChange = posY - m_lastMouseY; pitchChange *= 0.2f;

		m_pitch += pitchChange;
	}
}

const void Camera::CalculateAngleAroundPlayer()
{
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT))
	{
		double posX;
		glfwGetCursorPos(glfwGetCurrentContext(), &posX, NULL);

		float angleChange = posX - m_lastMouseX; angleChange *= 0.5f;

		m_angleAroundThePlayer -= angleChange;
	}
}

const float Camera::CalculateHorizontalDistance()
{
	return m_distanceFromPlayer * glm::cos(glm::radians(m_pitch));
}

const float Camera::CalculateVerticalDistance()
{
	return m_distanceFromPlayer * glm::sin(glm::radians(m_pitch));
}

const void Camera::CalculateCameraPosition(const float& horizontalDistance, const float& verticalDistance)
{
	float theta = m_player->GetRotation().y + m_angleAroundThePlayer;

	float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
	float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));

	m_position.x = m_player->GetPosition().x - offsetX;
	m_position.y = m_player->GetPosition().y + verticalDistance + m_playerHead;
	m_position.z = m_player->GetPosition().z - offsetZ;
}

void Camera::Scroll_Event(GLFWwindow* window, double x, double y)
{
	m_scrollY = y;
}
