#include "../pch.h"
#include "TerrainShader.hpp"


TerrainShader::TerrainShader()
	: ShaderProgram(TERRAIN_SHADER_FILE)
{
	BindAttributes();
	GetAllUniformLocations();
}

const void TerrainShader::LoadTransformationMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(m_location_transformationMatrix, matrix);
}

const void TerrainShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(m_location_projectionMatrix, matrix);
}

const void TerrainShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix;
	viewMatrix = Maths::CreateViewMatrix(camera);

	LoadMatrix4f(m_location_viewMatrix, viewMatrix);
}

const void TerrainShader::LoadLight(Light& light)
{
	LoadVector3F(m_location_lightPosition, light.GetPosition());
	LoadVector3F(m_location_lightColor, light.GetColor());
}

const void TerrainShader::LoadShineVariables(const float& damper, const float& ref)
{
	LoadFloat(m_location_shineDamper, damper);
	LoadFloat(m_location_reflectivity, ref);
}

const void TerrainShader::LoadSkyColor(const glm::vec3& skyColor)
{
	LoadVector3F(m_location_skyColor, skyColor);
}

void TerrainShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoords");
	BindAttribute(2, "normal");
}

void TerrainShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = GetUniformLocation("transformationMatrix");
	m_location_projectionMatrix = GetUniformLocation("projectionMatrix");
	m_location_viewMatrix = GetUniformLocation("viewMatrix");
	m_location_lightPosition = GetUniformLocation("lightPosition");
	m_location_lightColor = GetUniformLocation("lightColor");
	m_location_shineDamper = GetUniformLocation("shineDamper");
	m_location_reflectivity = GetUniformLocation("reflectivity");

	m_location_skyColor = GetUniformLocation("skyColor");
}
