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
	void LoadTransformationMatrix(const glm::mat4& matrix);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadLight(Light& light);
	void LoadShineVariables(const float& damper, const float& ref);
protected:
	// Functions
	void BindAttributes();
	void GetAllUniformLocations();
private:
	// Variables
	GLuint m_transformationMatrix_Location, m_projectionMatrix_Location, m_viewMatrix_Location;
	GLuint m_lightPosition_Location, m_lightColor_Location;
	GLuint m_shineDamper_Location, m_reflectivity_Location;
};
#endif // !TERRAINSHADER_HPP