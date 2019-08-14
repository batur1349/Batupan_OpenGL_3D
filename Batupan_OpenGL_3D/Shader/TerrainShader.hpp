#ifndef TERRAINSHADER_HPP
#define TERRAINSHADER_HPP

#include "ShaderProgram.hpp"
#include "../Entity/Light.hpp"
#include "../Entity/Camera.hpp"
#include "../Toolbox/Maths.hpp"
static const std::string TERRAIN_SHADER_FILE = "Shader/terrainShader";

class TerrainShader : public ShaderProgram
{
public:
	// Constructor
	TerrainShader();

	// Functions
	const void LoadTransformationMatrix(const glm::mat4& matrix);
	const void LoadProjectionMatrix(const glm::mat4& matrix);
	const void LoadViewMatrix(Camera& camera);
	const void LoadLight(Light& light);
	const void LoadShineVariables(const float& damper, const float& ref);
	const void LoadSkyColor(const glm::vec3& skyColor);
	const void ConnectTextureUnits();
protected:
	// Functions
	void BindAttributes();
	void GetAllUniformLocations();
private:
	// Variables
	GLuint m_location_transformationMatrix, m_location_projectionMatrix, m_location_viewMatrix;
	GLuint m_location_lightPosition, m_location_lightColor;
	GLuint m_location_shineDamper, m_location_reflectivity;
	GLuint m_location_skyColor;
	GLuint m_location_backgroundTexture, m_location_rTexture, m_location_gTexture, m_location_bTexture, m_location_blendMap;
};
#endif // !TERRAINSHADER_HPP