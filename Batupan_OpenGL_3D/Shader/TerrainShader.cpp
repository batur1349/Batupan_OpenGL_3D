#include "../pch.h"
#include "TerrainShader.hpp"


TerrainShader::TerrainShader()
	: ShaderProgram(TERRAIN_SHADER_FILE)
{
	BindAttributes();
	GetAllUniformLocations();
}

void TerrainShader::LoadTransformationMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(m_transformationMatrix_Location, matrix);
}

void TerrainShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(m_projectionMatrix_Location, matrix);
}

void TerrainShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix;
	viewMatrix = Maths::CreateViewMatrix(camera);

	LoadMatrix4f(m_viewMatrix_Location, viewMatrix);
}

void TerrainShader::LoadLight(Light& light)
{
	LoadVector3F(m_lightPosition_Location, light.GetPosition());
	LoadVector3F(m_lightColor_Location, light.GetColor());
}

void TerrainShader::LoadShineVariables(const float& damper, const float& ref)
{
	LoadFloat(m_shineDamper_Location, damper);
	LoadFloat(m_reflectivity_Location, ref);
}

void TerrainShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoords");
	BindAttribute(2, "normal");
}

void TerrainShader::GetAllUniformLocations()
{
	m_transformationMatrix_Location = GetUniformLocation("transformationMatrix");
	m_projectionMatrix_Location = GetUniformLocation("projectionMatrix");
	m_viewMatrix_Location = GetUniformLocation("viewMatrix");
	m_lightPosition_Location = GetUniformLocation("lightPosition");
	m_lightColor_Location = GetUniformLocation("lightColor");
	m_shineDamper_Location = GetUniformLocation("shineDamper");
	m_reflectivity_Location = GetUniformLocation("reflectivity");
}
