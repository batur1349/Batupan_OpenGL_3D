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
	const void LoadLights(const std::vector<Light>& lights);
	const void LoadShineVariables(const float& shineDamper, const float& reflectivity);
	const void LoadFakeLightning(const bool& useFakeLightning);
	const void LoadSkyColor(const glm::vec3& skyColor);
	const void LoadNumberOfRows(const int& nrOfRows);
	const void LoadNumberOfColumns(const int& nrOfCols);
	const void LoadOffset(const glm::vec2& offset);
protected:
	void BindAttributes();
	void GetAllUniformLocations();
private:
	static const int MAX_LIGHTS = 4;
	GLuint m_location_transformationMatrix, m_location_projectionMatrix, m_location_viewMatrix;
	GLuint m_location_lightColor[MAX_LIGHTS], m_location_lightPosition[MAX_LIGHTS], m_location_shineDamper, m_location_reflectivity;
	GLuint m_location_fakeLightning;
	GLuint m_location_skyColor;
	GLuint m_location_numberOfRows, m_location_numberOfColumns, m_location_offset;
};

#endif // !BASICSHADER_HPP