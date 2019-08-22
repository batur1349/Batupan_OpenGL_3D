#include "../pch.h"
#include "MousePicker.hpp"


MousePicker::MousePicker(Camera* camera, const glm::mat4& projectionMatrix, const std::vector<Terrain>& terrains)
	: m_camera(camera), m_projectionMatrix(projectionMatrix), m_terrains(terrains)
{
	m_viewMatrix = Maths::CreateViewMatrix(*camera);
}

const void MousePicker::Update()
{
	m_viewMatrix = m_camera->GetViewMatrix();
	m_currentRay = CalculateMouseRay();

	if (IntersectionInRange(0, RAY_RANGE, m_currentRay))
	{
		m_currentTerrainPoint = BinarySearch(0, 0, RAY_RANGE, m_currentRay);
	}
	else
	{
		m_currentTerrainPoint = glm::vec3(0, 0, 0);
	}
}

const glm::vec3 MousePicker::CalculateMouseRay()
{
	double mouseX = 400, mouseY = 300;
	//glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);

	glm::vec2 normalizedCoords = GetNormalizedDeviceCoordinates(mouseX, mouseY);
	glm::vec4 clipCoords(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
	glm::vec3 worldRay = ToWorldCoords(eyeCoords);

	return worldRay;
}

const glm::vec2 MousePicker::GetNormalizedDeviceCoordinates(const float& mouseX, const float& mouseY)
{
	int sizex = 960, sizey = 540;
	//glfwGetWindowSize(glfwGetCurrentContext(), &sizex, &sizey);

	float x = (2.f * mouseX) / sizex - 1;
	float y = (2.f * mouseY) / sizey - 1;

	return glm::vec2(x, -y);
}

const glm::vec4 MousePicker::ToEyeCoords(const glm::vec4& clipCoords)
{
	glm::vec4 eyeCoords = Maths::TransformMatrix(Maths::InvertMatrix(m_projectionMatrix), clipCoords);
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.f);
}

const glm::vec3 MousePicker::ToWorldCoords(const glm::vec4& eyeCoords)
{
	glm::mat4 invertedView = Maths::InvertMatrix(m_viewMatrix);
	glm::vec4 rayWorld = Maths::TransformMatrix(invertedView, eyeCoords);
	glm::vec3 mouseRay(rayWorld.x, rayWorld.y, rayWorld.z);

	return glm::normalize(mouseRay);
}

const glm::vec3 MousePicker::GetPointOnRay(const glm::vec3& ray, const float& distance)
{
	glm::vec3 camPos = m_camera->GetPosition();
	glm::vec3 scaledRay(ray.x * distance, ray.y * distance, ray.z * distance);

	return glm::vec3(camPos.x + scaledRay.x, camPos.y + scaledRay.y, camPos.z + scaledRay.z);
}

const glm::vec3 MousePicker::BinarySearch(const int& count, const float& start, const float& finish, const glm::vec3& ray)
{
	float half = start + ((finish - start) / 2.f);

	if (count >= RECURSION_COUNT)
	{
		glm::vec3 endPoint = GetPointOnRay(ray, half);
		return endPoint;
	}

	if (IntersectionInRange(start, half, ray))
	{
		return BinarySearch(count + 1, start, half, ray);
	}
	else
	{
		return BinarySearch(count + 1, half, finish, ray);
	}
}

const bool MousePicker::IntersectionInRange(const float& start, const float& finish, const glm::vec3& ray)
{
	glm::vec3 startPoint = GetPointOnRay(ray, start);
	glm::vec3 endPoint = GetPointOnRay(ray, finish);

	if (!IsUnderGround(startPoint) && IsUnderGround(endPoint))
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool MousePicker::IsUnderGround(const glm::vec3& testPoint)
{
	float minX = 999999, minZ = 999999, maxX = 0, maxZ = 0, height = 0;

	for (int i = 0; i < m_terrains.size(); i++)
	{
		if (m_terrains.at(i).GetStartX() < minX)
			minX = m_terrains.at(i).GetStartX();
		if (m_terrains.at(i).GetStartZ() < minZ)
			minZ = m_terrains.at(i).GetStartZ();
		if (m_terrains.at(i).GetEndX() > maxX)
			maxX = m_terrains.at(i).GetEndX();
		if (m_terrains.at(i).GetEndZ() > maxZ)
			maxZ = m_terrains.at(i).GetEndZ();
	}

	if (testPoint.x > minX && testPoint.x < maxX && testPoint.z > minZ && testPoint.z < maxZ)
	{
		Terrain terrain = GetTerrain(testPoint.x, testPoint.z);
		height = terrain.GetHeightOfTerrain(testPoint.x, testPoint.z);

		if (testPoint.y < height)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

const Terrain& MousePicker::GetTerrain(float worldX, float worldZ)
{
	for (int i = 0; i < m_terrains.size(); i++)
	{
		if (m_terrains.at(i).GetStartX() < worldX && m_terrains.at(i).GetEndX() > worldX &&
			m_terrains.at(i).GetStartZ() < worldZ && m_terrains.at(i).GetEndZ() > worldZ)
		{
			return m_terrains.at(i);
		}
	}
}
