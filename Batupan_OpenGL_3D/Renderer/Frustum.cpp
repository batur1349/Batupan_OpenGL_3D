#include "../pch.h"
#include "Frustum.hpp"
#include "MasterRenderer.hpp"

Frustum::Frustum()
{
	int wWidth, wHeight;
	glfwGetWindowSize(glfwGetCurrentContext(), &wWidth, &wHeight);
	m_aspect = (float)wWidth / (float)wHeight;

	m_projectionMatrix = Maths::CreateProjectionMatrix(MasterRenderer::FOV, MasterRenderer::NEAR_PLANE, MasterRenderer::FAR_PLANE);
}

void Frustum::CalculateFrustumPlanes(const glm::mat4& view)
{
	const glm::mat4& v = view; //const glm::mat4& p = pojection;

	m_clipMatrix[0][0] = v[0][0] * m_projectionMatrix[0][0] + v[0][1] * m_projectionMatrix[1][0] + v[0][2] * m_projectionMatrix[2][0] + v[0][3] * m_projectionMatrix[3][0];
	m_clipMatrix[1][0] = v[0][0] * m_projectionMatrix[0][1] + v[0][1] * m_projectionMatrix[1][1] + v[0][2] * m_projectionMatrix[2][1] + v[0][3] * m_projectionMatrix[3][1];
	m_clipMatrix[2][0] = v[0][0] * m_projectionMatrix[0][2] + v[0][1] * m_projectionMatrix[1][2] + v[0][2] * m_projectionMatrix[2][2] + v[0][3] * m_projectionMatrix[3][2];
	m_clipMatrix[3][0] = v[0][0] * m_projectionMatrix[0][3] + v[0][1] * m_projectionMatrix[1][3] + v[0][2] * m_projectionMatrix[2][3] + v[0][3] * m_projectionMatrix[3][3];
	m_clipMatrix[0][1] = v[1][0] * m_projectionMatrix[0][0] + v[1][1] * m_projectionMatrix[1][0] + v[1][2] * m_projectionMatrix[2][0] + v[1][3] * m_projectionMatrix[3][0];
	m_clipMatrix[1][1] = v[1][0] * m_projectionMatrix[0][1] + v[1][1] * m_projectionMatrix[1][1] + v[1][2] * m_projectionMatrix[2][1] + v[1][3] * m_projectionMatrix[3][1];
	m_clipMatrix[2][1] = v[1][0] * m_projectionMatrix[0][2] + v[1][1] * m_projectionMatrix[1][2] + v[1][2] * m_projectionMatrix[2][2] + v[1][3] * m_projectionMatrix[3][2];
	m_clipMatrix[3][1] = v[1][0] * m_projectionMatrix[0][3] + v[1][1] * m_projectionMatrix[1][3] + v[1][2] * m_projectionMatrix[2][3] + v[1][3] * m_projectionMatrix[3][3];
	m_clipMatrix[0][2] = v[2][0] * m_projectionMatrix[0][0] + v[2][1] * m_projectionMatrix[1][0] + v[2][2] * m_projectionMatrix[2][0] + v[2][3] * m_projectionMatrix[3][0];
	m_clipMatrix[1][2] = v[2][0] * m_projectionMatrix[0][1] + v[2][1] * m_projectionMatrix[1][1] + v[2][2] * m_projectionMatrix[2][1] + v[2][3] * m_projectionMatrix[3][1];
	m_clipMatrix[2][2] = v[2][0] * m_projectionMatrix[0][2] + v[2][1] * m_projectionMatrix[1][2] + v[2][2] * m_projectionMatrix[2][2] + v[2][3] * m_projectionMatrix[3][2];
	m_clipMatrix[3][2] = v[2][0] * m_projectionMatrix[0][3] + v[2][1] * m_projectionMatrix[1][3] + v[2][2] * m_projectionMatrix[2][3] + v[2][3] * m_projectionMatrix[3][3];
	m_clipMatrix[0][3] = v[3][0] * m_projectionMatrix[0][0] + v[3][1] * m_projectionMatrix[1][0] + v[3][2] * m_projectionMatrix[2][0] + v[3][3] * m_projectionMatrix[3][0];
	m_clipMatrix[1][3] = v[3][0] * m_projectionMatrix[0][1] + v[3][1] * m_projectionMatrix[1][1] + v[3][2] * m_projectionMatrix[2][1] + v[3][3] * m_projectionMatrix[3][1];
	m_clipMatrix[2][3] = v[3][0] * m_projectionMatrix[0][2] + v[3][1] * m_projectionMatrix[1][2] + v[3][2] * m_projectionMatrix[2][2] + v[3][3] * m_projectionMatrix[3][2];
	m_clipMatrix[3][3] = v[3][0] * m_projectionMatrix[0][3] + v[3][1] * m_projectionMatrix[1][3] + v[3][2] * m_projectionMatrix[2][3] + v[3][3] * m_projectionMatrix[3][3];

	m_planes[PLANE_RIGHT].x = m_clipMatrix[3][0] - m_clipMatrix[0][0];
	m_planes[PLANE_RIGHT].y = m_clipMatrix[3][1] - m_clipMatrix[0][1];
	m_planes[PLANE_RIGHT].z = m_clipMatrix[3][2] - m_clipMatrix[0][2];
	m_planes[PLANE_RIGHT].w = m_clipMatrix[3][3] - m_clipMatrix[0][3];

	m_planes[PLANE_LEFT].x = m_clipMatrix[3][0] + m_clipMatrix[0][0];
	m_planes[PLANE_LEFT].y = m_clipMatrix[3][1] + m_clipMatrix[0][1];
	m_planes[PLANE_LEFT].z = m_clipMatrix[3][2] + m_clipMatrix[0][2];
	m_planes[PLANE_LEFT].w = m_clipMatrix[3][3] + m_clipMatrix[0][3];

	m_planes[PLANE_BOTTOM].x = m_clipMatrix[3][0] + m_clipMatrix[1][0];
	m_planes[PLANE_BOTTOM].y = m_clipMatrix[3][1] + m_clipMatrix[1][1];
	m_planes[PLANE_BOTTOM].z = m_clipMatrix[3][2] + m_clipMatrix[1][2];
	m_planes[PLANE_BOTTOM].w = m_clipMatrix[3][3] + m_clipMatrix[1][3];

	m_planes[PLANE_TOP].x = m_clipMatrix[3][0] - m_clipMatrix[1][0];
	m_planes[PLANE_TOP].y = m_clipMatrix[3][1] - m_clipMatrix[1][1];
	m_planes[PLANE_TOP].z = m_clipMatrix[3][2] - m_clipMatrix[1][2];
	m_planes[PLANE_TOP].w = m_clipMatrix[3][3] - m_clipMatrix[1][3];

	m_planes[PLANE_BACK].x = m_clipMatrix[3][0] - m_clipMatrix[2][0];
	m_planes[PLANE_BACK].y = m_clipMatrix[3][1] - m_clipMatrix[2][1];
	m_planes[PLANE_BACK].z = m_clipMatrix[3][2] - m_clipMatrix[2][2];
	m_planes[PLANE_BACK].w = m_clipMatrix[3][3] - m_clipMatrix[2][3];

	m_planes[PLANE_FRONT].x = m_clipMatrix[3][0] + m_clipMatrix[2][0];
	m_planes[PLANE_FRONT].y = m_clipMatrix[3][1] + m_clipMatrix[2][1];
	m_planes[PLANE_FRONT].z = m_clipMatrix[3][2] + m_clipMatrix[2][2];
	m_planes[PLANE_FRONT].w = m_clipMatrix[3][3] + m_clipMatrix[2][3];

	for (int i = 0; i < 6; i++)
	{
		m_planes[i] = glm::normalize(m_planes[i]);
	}
}

bool Frustum::PointInFrustum(const glm::vec3& point)
{
	for (int i = 0; i < 6; i++)
	{
		const float pos = m_planes[i].w;
		const glm::vec3 normal = glm::vec3(m_planes[i]);

		if (glm::dot(normal, point) + pos < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::SphereInFrustum(const glm::vec3& point, const float& radius)
{
	for (int i = 0; i < 6; i++)
	{
		const float& pos = m_planes[i].w;
		const glm::vec3& normal = glm::vec3(m_planes[i]);

		if (glm::dot(normal, point) + pos <= -glm::normalize(glm::vec4(point, radius)).w)
		{
			return false;
		}
	}

	return true;
}
