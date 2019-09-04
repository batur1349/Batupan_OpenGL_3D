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

const void TerrainShader::LoadLights(const std::vector<Light>& lights)
{
	for (size_t i = 0; i < MAX_LIGHTS; i++)
	{
		if (i < lights.size())
		{
			LoadVector3F(m_location_lightColor[i], lights.at(i).GetColor());
			LoadVector3F(m_location_lightPosition[i], lights.at(i).GetPosition());
			LoadVector3F(m_location_attenuation[i], lights.at(i).GetAttenuation());
		}
		else
		{
			LoadVector3F(m_location_lightColor[i], glm::vec3(0.0f));
			LoadVector3F(m_location_lightPosition[i], glm::vec3(0.0f));
			LoadVector3F(m_location_attenuation[i], glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
}

const void TerrainShader::LoadLamps(const std::vector<Lamp>& lamps)
{
	for (size_t i = 0; i < MAX_LIGHTS; i++)
	{
		if (i < lamps.size())
		{
			LoadVector3F(m_location_lightColor[i], lamps.at(i).GetLight().GetColor());
			LoadVector3F(m_location_lightPosition[i], lamps.at(i).GetLight().GetPosition());
			LoadVector3F(m_location_attenuation[i], lamps.at(i).GetLight().GetAttenuation());
		}
		else
		{
			LoadVector3F(m_location_lightColor[i], glm::vec3(0.0f));
			LoadVector3F(m_location_lightPosition[i], glm::vec3(0.0f));
			LoadVector3F(m_location_attenuation[i], glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
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

const void TerrainShader::LoadPlane(const glm::vec4& plane)
{
	LoadVector4F(m_location_plane, plane);
}

const void TerrainShader::ConnectTextureUnits()
{
	LoadInt(m_location_backgroundTexture, 0);
	LoadInt(m_location_rTexture, 1);
	LoadInt(m_location_gTexture, 2);
	LoadInt(m_location_bTexture, 3);
	LoadInt(m_location_blendMap, 4);
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
	for (size_t i = 0; i < MAX_LIGHTS; i++)
	{
		m_location_lightPosition[i] = GetUniformLocation("lightPosition[" + std::to_string(i) + "]");
		m_location_lightColor[i] = GetUniformLocation("lightColor[" + std::to_string(i) + "]");
		m_location_attenuation[i] = GetUniformLocation("attenuation[" + std::to_string(i) + "]");
	}
	m_location_shineDamper = GetUniformLocation("shineDamper");
	m_location_reflectivity = GetUniformLocation("reflectivity");

	m_location_skyColor = GetUniformLocation("skyColor");

	m_location_backgroundTexture = GetUniformLocation("backgroundTexture");
	m_location_rTexture = GetUniformLocation("rTexture");
	m_location_gTexture = GetUniformLocation("gTexture");
	m_location_bTexture = GetUniformLocation("bTexture");
	m_location_blendMap = GetUniformLocation("blendTexture");

	m_location_plane = GetUniformLocation("plane");
}
