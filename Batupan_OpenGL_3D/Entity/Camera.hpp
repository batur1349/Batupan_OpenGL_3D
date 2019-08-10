#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera
{
public:
	Camera();

	// Methods
	const void Move();

	// Getters
	inline glm::vec3& GetPosition() { return m_position; }
	inline float& GetPitch() { return m_pitch; }
	inline float& GetYaw() { return m_yaw; }
	inline float& GetRoll() { return m_roll; }
private:
	glm::vec3 m_position;
	float m_pitch, m_yaw, m_roll;
};

#endif // !CAMERA_HPP