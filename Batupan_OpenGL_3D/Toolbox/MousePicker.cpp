#include "../pch.h"
#include "MousePicker.hpp"


MousePicker::MousePicker(Camera* camera, const glm::mat4& projectionMatrix, const std::vector<Terrain>& terrains)
	: _camera(camera), m_projectionMatrix(projectionMatrix), _terrains(terrains)
{
	m_viewMatrix = Maths::CreateViewMatrix(*camera);
}

const void MousePicker::Update()
{
	m_viewMatrix = _camera->GetViewMatrix();

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
	static double mouseX, mouseY;
	glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);

	glm::vec2 normalizedCoords = GetNormalizedDeviceCoordinates(mouseX, mouseY);
	glm::vec4 clipCoords(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
	glm::vec3 worldRay = ToWorldCoords(eyeCoords);

	return worldRay;
}

const glm::vec2 MousePicker::GetNormalizedDeviceCoordinates(const float& mouseX, const float& mouseY)
{
	static int sizex, sizey;
	glfwGetWindowSize(glfwGetCurrentContext(), &sizex, &sizey);

	float x = (2.f * mouseX) / sizex - 1;
	float y = (2.f * mouseY) / sizey - 1;

	return glm::vec2(x, -y);
}

const glm::vec4 MousePicker::ToEyeCoords(const glm::vec4& clipCoords)
{
	glm::mat4 invertedProjectionMatrix = Maths::InvertMatrix(m_projectionMatrix);
	glm::vec4 eyeCoords = Maths::TransformMatrix(invertedProjectionMatrix, clipCoords);

	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.f);
}

const glm::vec3 MousePicker::ToWorldCoords(const glm::vec4& eyeCoords)
{
	glm::mat4 invertedView = Maths::InvertMatrix(m_viewMatrix);
	glm::vec4 rayWorld = Maths::TransformMatrix(invertedView, eyeCoords);
	glm::vec3 mouseRay(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = glm::normalize(mouseRay);

	return mouseRay;
}

const glm::vec3 MousePicker::GetPointOnRay(const glm::vec3& ray, const float& distance)
{
	glm::vec3 camPos = _camera->GetPosition();
	glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
	glm::vec3 scaledRay(ray.x * distance, ray.y * distance, ray.z * distance);

	return glm::vec3(start.x + scaledRay.x, start.y + scaledRay.y, start.z + scaledRay.z);
}

const glm::vec3 MousePicker::BinarySearch(const int& count, const float& start, const float& finish, const glm::vec3& ray)
{
	float half = start + ((finish - start) / 2.f);

	if (count >= RECURSION_COUNT)
	{
		glm::vec3 endPoint = GetPointOnRay(ray, half);
		//Terrain* terrain = GetTerrain(endPoint.x, endPoint.z);
		//Terrain terrain = GetTerrain(endPoint.x, endPoint.z);

		return endPoint;
		//if (terrain != NULL)
		//{
		//	return endPoint;
		//}
		//else
		//{
		//	return glm::vec3(0, 0, 0);
		//}
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
	Terrain terrain = GetTerrain(testPoint.x, testPoint.z);
	float height = 0;

	//if (terrain != NULL)
	//{
	//	height = terrain->GetHeightOfTerrain(testPoint.x, testPoint.z);
	//}
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

const Terrain& MousePicker::GetTerrain(float worldX, float worldZ)
{
	for (int i = 0; i < _terrains.size(); i++)
	{
		if (_terrains.at(i).GetStartX() < worldX && _terrains.at(i).GetEndX() > worldX &&
			_terrains.at(i).GetStartZ() < worldZ && _terrains.at(i).GetEndZ() > worldZ)
		{
			return _terrains.at(i);
		}
		//else
		//{
		//	//return nullptr;
		//}
	}
}
