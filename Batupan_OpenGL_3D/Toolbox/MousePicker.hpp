#ifndef MOUSEPICKER_HPP
#define MOUSEPICKER_HPP

#include "../Entity/Camera.hpp"
#include "../Terrain/Terrain.hpp"
#include "Maths.hpp"

class MousePicker
{
public:
	MousePicker(Camera* camera, const glm::mat4& projectionMatrix, const std::vector<Terrain>& terrains);

	// Getters
	const inline glm::vec3& GetCurrentRay() { return m_currentRay; }
	const inline glm::vec3& GetCurrentTerrainPoint() { return m_currentTerrainPoint; }

	// Functions
	const void Update();
private:
	// Variables
	glm::vec3 m_currentRay;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	Camera* _camera;
	const int RECURSION_COUNT = 50; //200
	const float RAY_RANGE = 300; // 600
	std::vector<Terrain> _terrains;
	glm::vec3 m_currentTerrainPoint;

	// Functions
	const glm::vec3 CalculateMouseRay();
	const glm::vec2 GetNormalizedDeviceCoordinates(const float& mouseX, const float& mouseY);
	const glm::vec4 ToEyeCoords(const glm::vec4& clipCoords);
	const glm::vec3 ToWorldCoords(const glm::vec4& eyeCoords);

	const glm::vec3 GetPointOnRay(const glm::vec3& ray, const float& distance);
	const glm::vec3 BinarySearch(const int& count, const float& start, const float& finish, const glm::vec3& ray);
	const bool IntersectionInRange(const float& start, const float& finish, const glm::vec3& ray);
	const bool IsUnderGround(const glm::vec3& testPoint);
	const Terrain& GetTerrain(float worldX, float worldZ);
};

#endif // !MOUSEPICKER_HPP