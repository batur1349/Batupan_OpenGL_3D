#ifndef BASICSHADER_HPP
#define BASICSHADER_HPP

#include "ShaderProgram.hpp"
#include "../Entity/Camera.hpp"
#include "../Toolbox/Maths.hpp"
#include "../Entity/Light.hpp"

static const std::string BASIC_SHADER_FILE = "Shader/basicShader";

class BasicShader : public ShaderProgram
{
public:
	BasicShader();

	const void LoadTransformationMatrix(const glm::mat4& matrix);
	const void LoadProjectionMatrix(const glm::mat4& matrix);
	const void LoadViewMatrix(Camera* camera);
	const void LoadLight(Light& light);
	const void LoadShineVariables(const float& shineDamper, const float& reflectivity);
protected:
	void BindAttributes();
	void GetAllUniformLocations();
private:
	GLuint m_location_transformationMatrix, m_location_projectionMatrix, m_location_viewMatrix;
	GLuint m_location_lightColor, m_location_lightPosition, m_location_shineDamper, m_location_reflectivity;
};

#endif // !BASICSHADER_HPP