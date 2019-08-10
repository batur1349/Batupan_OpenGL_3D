#ifndef BASICSHADER_HPP
#define BASICSHADER_HPP

#include "ShaderProgram.hpp"
#include "../Entity/Camera.hpp"
#include "../Toolbox/Maths.hpp"

static const std::string SHADER_FILE = "Shader/basicShader";

class BasicShader : public ShaderProgram
{
public:
	BasicShader();

	const void LoadTransformationMatrix(const glm::mat4& matrix);
	const void LoadProjectionMatrix(const glm::mat4& matrix);
	const void LoadViewMatrix(Camera* camera);
protected:
	void BindAttributes();
	void GetAllUniformLocations();
private:
	GLuint m_location_transformationMatrix, m_location_projectionMatrix, m_location_viewMatrix;
};

#endif // !BASICSHADER_HPP