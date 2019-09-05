#ifndef WATERSHADER_HPP
#define WATERSHADER_HPP

#include "../Entity/Camera.hpp"
#include "../Toolbox/Maths.hpp"
#include "../Shader/ShaderProgram.hpp"
#include "../Entity/Lamp.hpp"
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
	void LoadMoveFactor(const float& factor);
	void LoadLight(const Lamp& lamp);
	void ConnectTextureUnits();
private:
	GLuint m_location_modelMatrix, m_location_viewMatrix, m_location_projectionMatrix;
	GLuint m_location_reflectionTexture, m_location_refractionTexture;
	GLuint m_location_dudvMap, m_location_moveFactor;
	GLuint m_location_cameraPosition;
	GLuint m_location_normalMap, m_location_lightPosition, m_location_lightColor;
	GLuint m_location_depthMap;
};

#endif // !WATERSHADER_HPP