#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Player.hpp"

class Camera
{
public:
	Camera(Player* player);

	// Methods
	const void Update();

	// Getters
	inline glm::vec3& GetPosition() { return m_position; }
	inline float& GetPitch() { return m_pitch; }
	inline float& GetYaw() { return m_yaw; }
	inline float& GetRoll() { return m_roll; }
	const glm::mat4 GetViewMatrix();
private:
	Player* m_player;
	glm::vec3 m_position, m_worldUP, m_front;
	float m_pitch, m_yaw, m_roll, m_playerHead = 10.0f;
	float m_distanceFromPlayer = 50.0f, m_angleAroundThePlayer = 0.0f;
	static int m_scrollY;
	double m_lastMouseX, m_lastMouseY;

	// Functions
	const void UpdateInput();
	const void CalculateZoom();
	const void CalculatePitch();
	const void CalculateAngleAroundPlayer();

	const float CalculateHorizontalDistance();
	const float CalculateVerticalDistance();
	const void CalculateCameraPosition(const float& horizontalDistance, const float& verticalDistance);

	static void Scroll_Event(GLFWwindow* window, double x, double y);
};

#endif // !CAMERA_HPP