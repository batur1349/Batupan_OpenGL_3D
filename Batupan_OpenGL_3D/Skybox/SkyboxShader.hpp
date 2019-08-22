#ifndef SKYBOXSHADER_HPP
#define SKYBOXSHADER_HPP

#include "../Toolbox/Maths.hpp"
#include "../Shader/ShaderProgram.hpp"
#include "../Entity/Camera.hpp"
static const std::string SKYBOX_SHADER_FILE = "Skybox/skyboxShader";
static const float ROTATE_SPEED = 1.0f;

class SkyboxShader : public ShaderProgram
{
public:
	// Constructor
	SkyboxShader();

	// Functions
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera, const float& dt);
	void LoadFogColor(const glm::vec3& color);
	void LoadBlendFactor(const float& blendFactor);
	void ConnectTextureUnits();
protected:
	void GetAllUniformLocations();
	void BindAttributes();
private:
	// Variables
	GLuint m_location_projectionMatrix, m_location_viewMatrix;
	GLuint m_location_fogColor, m_location_blendFactor;
	GLuint m_location_cubeMap, m_location_cubeMap2;
	float m_rotation = 0.0f;
};

#endif // !SKYBOXSHADER_HPP