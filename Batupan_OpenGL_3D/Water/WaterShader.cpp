#include "../pch.h"
#include "WaterShader.hpp"


WaterShader::WaterShader()
	: ShaderProgram(WATER_SHADER_FILE)
{
	BindAttributes();
	GetAllUniformLocations();
}

void WaterShader::BindAttributes()
{
	BindAttribute(0, "position");
}

void WaterShader::GetAllUniformLocations()
{
	m_location_modelMatrix = GetUniformLocation("modelMatrix");
	m_location_viewMatrix = GetUniformLocation("viewMatrix");
	m_location_projectionMatrix = GetUniformLocation("projectionMatrix");
}

void WaterShader::LoadProjectionMatrix(const glm::mat4& projectionMatrix)
{
	LoadMatrix4f(m_location_projectionMatrix, projectionMatrix);
}

void WaterShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(camera);

	LoadMatrix4f(m_location_viewMatrix, viewMatrix);
}

void WaterShader::LoadModelMatrix(const glm::mat4& modelMatrix)
{
	LoadMatrix4f(m_location_modelMatrix, modelMatrix);
}
