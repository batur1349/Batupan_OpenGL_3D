#include "../pch.h"
#include "BasicShader.hpp"


BasicShader::BasicShader()
	: ShaderProgram(SHADER_FILE)
{
	BindAttributes();
	GetAllUniformLocations();
}

const void BasicShader::LoadTransformationMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(m_location_transformationMatrix, matrix);
}

const void BasicShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(m_location_projectionMatrix, matrix);
}

const void BasicShader::LoadViewMatrix(Camera* camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(*camera);
	LoadMatrix4f(m_location_viewMatrix, viewMatrix);
}

void BasicShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoords");
}

void BasicShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = GetUniformLocation("transformationMatrix");
	m_location_projectionMatrix = GetUniformLocation("projectionMatrix");
	m_location_viewMatrix = GetUniformLocation("viewMatrix");
}
