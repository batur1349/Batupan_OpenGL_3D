#ifndef SKYBOXSHADER_HPP
#define SKYBOXSHADER_HPP

#include "../Toolbox/Maths.hpp"
#include "../Shader/ShaderProgram.hpp"
#include "../Entity/Camera.hpp"
static const std::string SKYBOX_SHADER_FILE = "Skybox/skyboxShader";

class SkyboxShader : public ShaderProgram
{
public:
	// Constructor
	SkyboxShader();

	// Functions
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
protected:
	void GetAllUniformLocations();
	void BindAttributes();
private:
	// Variables
	GLuint _location_projectionMatrix, _location_viewMatrix;
};

#endif // !SKYBOXSHADER_HPP