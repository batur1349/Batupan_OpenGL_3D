#ifndef MATHS_HPP
#define MATHS_HPP

#include "../Entity/Camera.hpp"

class Maths
{
public:
	static glm::mat4 CreateTransformationMatrix(const glm::vec2& translation, const glm::vec2& scale); // TODO ROTATION
	static glm::mat4 CreateTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
	static glm::mat4 CreateViewMatrix(Camera& camera);
	static glm::mat4 InvertMatrix(const glm::mat4& matrix);
	static glm::vec4 TransformMatrix(const glm::mat4& matrix, const glm::vec4& vector);
	static float BarryCentric(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& position);
private:
	static float Determinant(const glm::mat4& matrix);
	static float Determinant3x3(float t00, float t01, float t02, float t10, float t11, float t12, float t20, float t21, float t22);
};

#endif // !MATHS_HPP