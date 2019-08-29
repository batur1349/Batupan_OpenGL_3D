#ifndef WATERSHADER_HPP
#define WATERSHADER_HPP

#include "../Entity/Camera.hpp"
#include "../Toolbox/Maths.hpp"
#include "../Shader/ShaderProgram.hpp"
static const std::string WATER_SHADER_FILE = "Water/waterShader";

class WaterShader : public ShaderProgram
{
public:
	WaterShader();

	void BindAttributes();
	void GetAllUniformLocations();

	void LoadProjectionMatrix(const glm::mat4& projectionMatrix);
	void LoadViewMatrix(Camera& camera);
	void LoadModelMatrix(const glm::mat4& modelMatrix);
private:
	GLuint m_location_modelMatrix, m_location_viewMatrix, m_location_projectionMatrix;
};

#endif // !WATERSHADER_HPP