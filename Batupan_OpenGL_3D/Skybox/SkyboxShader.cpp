#include "../pch.h"
#include "SkyboxShader.hpp"


SkyboxShader::SkyboxShader()
	: ShaderProgram(SKYBOX_SHADER_FILE)
{
	BindAttributes();
	GetAllUniformLocations();
}

void SkyboxShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(_location_projectionMatrix, matrix);
}

void SkyboxShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 matrix;
	matrix = Maths::CreateViewMatrix(camera);

	matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0;

	LoadMatrix4f(_location_viewMatrix, matrix);
}

void SkyboxShader::GetAllUniformLocations()
{
	_location_projectionMatrix = GetUniformLocation("projectionMatrix");
	_location_viewMatrix = GetUniformLocation("viewMatrix");
}

void SkyboxShader::BindAttributes()
{
	BindAttribute(0, "position");
}