#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP

#include <array>
#include <glm.hpp>
#include "../Toolbox/Maths.hpp"

class Frustum
{
public:
	enum side { FrustumPlane_Right = 0, FrustumPlane_Left, FrustumPlane_Top, FrustumPlane_Bottom, FrustumPlane_Far, FrustumPlane_Near };
	enum Plane { PLANE_BACK = 0, PLANE_FRONT, PLANE_RIGHT, PLANE_LEFT, PLANE_TOP, PLANE_BOTTOM };

	Frustum();

	void CalculateFrustumPlanes(const glm::mat4& view);
	bool PointInFrustum(const glm::vec3& point);
	bool SphereInFrustum(const glm::vec3& point, const float& radius);
private:
	float m_aspect;
	glm::mat4 m_projectionMatrix, m_clipMatrix;
	std::array<glm::vec4, 6> m_planes;
};

#endif // !FRUSTUM_HPP