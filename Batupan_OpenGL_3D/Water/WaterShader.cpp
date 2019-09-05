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

	m_location_reflectionTexture = GetUniformLocation("reflectionTexture");
	m_location_refractionTexture = GetUniformLocation("refractionTexture");

	m_location_dudvMap = GetUniformLocation("dudvMap");
	m_location_moveFactor = GetUniformLocation("moveFactor");

	m_location_cameraPosition = GetUniformLocation("cameraPosition");

	m_location_normalMap = GetUniformLocation("normalMap");
	m_location_lightPosition = GetUniformLocation("lightPosition");
	m_location_lightColor = GetUniformLocation("lightColor");
}

void WaterShader::LoadProjectionMatrix(const glm::mat4& projectionMatrix)
{
	LoadMatrix4f(m_location_projectionMatrix, projectionMatrix);
}

void WaterShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(camera);

	LoadMatrix4f(m_location_viewMatrix, viewMatrix);
	LoadVector3F(m_location_cameraPosition, camera.GetPosition());
}

void WaterShader::LoadModelMatrix(const glm::mat4& modelMatrix)
{
	LoadMatrix4f(m_location_modelMatrix, modelMatrix);
}

void WaterShader::LoadMoveFactor(const float& factor)
{
	LoadFloat(m_location_moveFactor, factor);
}

void WaterShader::LoadLight(const Lamp& lamp)
{
	LoadVector3F(m_location_lightPosition, lamp.GetLightPosition());
	LoadVector3F(m_location_lightColor, lamp.GetLight().GetColor());
}

void WaterShader::ConnectTextureUnits()
{
	LoadInt(m_location_reflectionTexture, 0);
	LoadInt(m_location_refractionTexture, 1);
	LoadInt(m_location_dudvMap, 2);
	LoadInt(m_location_normalMap, 3);
}
