#include "../pch.h"
#include "BasicShader.hpp"


BasicShader::BasicShader()
	: ShaderProgram(BASIC_SHADER_FILE)
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

const void BasicShader::LoadLight(Light& light)
{
	LoadVector3F(m_location_lightColor, light.GetColor());
	LoadVector3F(m_location_lightPosition, light.GetPosition());
}

const void BasicShader::LoadShineVariables(const float& shineDamper, const float& reflectivity)
{
	LoadFloat(m_location_shineDamper, shineDamper);
	LoadFloat(m_location_reflectivity, reflectivity);
}

const void BasicShader::LoadFakeLightning(const bool& useFakeLightning)
{
	if (useFakeLightning)
		LoadFloat(m_location_fakeLightning, 1.0f);
	else
		LoadFloat(m_location_fakeLightning, 0.0f);
}

const void BasicShader::LoadSkyColor(const glm::vec3& skyColor)
{
	LoadVector3F(m_location_skyColor, skyColor);
}

const void BasicShader::LoadNumberOfRows(const int& nrOfRows)
{
	LoadFloat(m_location_numberOfRows, nrOfRows);
}

const void BasicShader::LoadOffset(const glm::vec2& offset)
{
	LoadVector2f(m_location_offset, offset);
}

void BasicShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoords");
	BindAttribute(2, "normal");
}

void BasicShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = GetUniformLocation("transformationMatrix");
	m_location_projectionMatrix = GetUniformLocation("projectionMatrix");
	m_location_viewMatrix = GetUniformLocation("viewMatrix");

	m_location_lightPosition = GetUniformLocation("lightPosition");
	m_location_lightColor = GetUniformLocation("lightColor");
	m_location_shineDamper = GetUniformLocation("shineDamper");
	m_location_reflectivity = GetUniformLocation("reflectivity");

	m_location_fakeLightning = GetUniformLocation("useFakeLightning");
	m_location_skyColor = GetUniformLocation("skyColor");

	m_location_numberOfRows = GetUniformLocation("numberOfRows");
	m_location_offset = GetUniformLocation("offset");
}
