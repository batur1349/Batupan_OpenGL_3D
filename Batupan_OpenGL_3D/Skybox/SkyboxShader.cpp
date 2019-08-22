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
	LoadMatrix4f(m_location_projectionMatrix, matrix);
}

void SkyboxShader::LoadViewMatrix(Camera& camera, const float& dt)
{
	glm::mat4 matrix;
	matrix = Maths::CreateViewMatrix(camera);

	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;

	m_rotation += ROTATE_SPEED * dt;
	matrix = glm::rotate(matrix, glm::radians(m_rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	LoadMatrix4f(m_location_viewMatrix, matrix);
}

void SkyboxShader::LoadFogColor(const glm::vec3& color)
{
	LoadVector3F(m_location_fogColor, color);
}

void SkyboxShader::LoadBlendFactor(const float& blendFactor)
{
	LoadFloat(m_location_blendFactor, blendFactor);
}

void SkyboxShader::ConnectTextureUnits()
{
	LoadInt(m_location_cubeMap, 0);
	LoadInt(m_location_cubeMap2, 1);
}

void SkyboxShader::GetAllUniformLocations()
{
	m_location_projectionMatrix = GetUniformLocation("projectionMatrix");
	m_location_viewMatrix = GetUniformLocation("viewMatrix");
	m_location_fogColor = GetUniformLocation("fogColor");
	m_location_blendFactor = GetUniformLocation("blendFactor");
	m_location_cubeMap = GetUniformLocation("cubeMap");
	m_location_cubeMap2 = GetUniformLocation("cubeMap2");
}

void SkyboxShader::BindAttributes()
{
	BindAttribute(0, "position");
}