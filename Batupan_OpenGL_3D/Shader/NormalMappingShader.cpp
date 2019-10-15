#include "../pch.h"
#include "NormalMappingShader.hpp"


NormalMappingShader::NormalMappingShader()
	: ShaderProgram(NORMALMAPPING_SHADER_FILE)
{
	BindAttributes();
	ConnectTextureUnits();
	GetAllUniformLocations();
}

void NormalMappingShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoordinates");
	BindAttribute(2, "normal");
	BindAttribute(3, "tangent");
}

void NormalMappingShader::GetAllUniformLocations()
{
	location_transformationMatrix = GetUniformLocation("transformationMatrix");
	location_projectionMatrix = GetUniformLocation("projectionMatrix");
	location_viewMatrix = GetUniformLocation("viewMatrix");
	location_numberOfRows = GetUniformLocation("numberOfRows");
	location_textureOffset = GetUniformLocation("offset");
	location_clipPlane = GetUniformLocation("plane");

	location_modelTexture = GetUniformLocation("modelTexture");
	location_normalMap = GetUniformLocation("normalMap");
	location_shineDamper = GetUniformLocation("shineDamper");
	location_reflectivity = GetUniformLocation("reflectivity");
	location_skyColor = GetUniformLocation("skyColour");

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		std::string iStr = std::to_string(i);
		location_lightPosition[i] = GetUniformLocation("lightPositionEyeSpace[" + iStr + "]");
		location_lightColor[i] = GetUniformLocation("lightColour[" + iStr + "]");
		location_attenuation[i] = GetUniformLocation("attenuation[" + iStr + "]");
	}
}

void NormalMappingShader::ConnectTextureUnits()
{
	LoadInt(location_modelTexture, 0);
	LoadInt(location_normalMap, 1);
}

void NormalMappingShader::LoadShineVariables(const float& damper, const float& reflectivity)
{
	LoadFloat(location_shineDamper, damper);
	LoadFloat(location_reflectivity, reflectivity);
}

void NormalMappingShader::LoadTransformationMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(location_transformationMatrix, matrix);
}

void NormalMappingShader::LoadLamps(const std::vector<Lamp>& lamps)
{
	for (int i = 0; i < MAX_LIGHTS; i++) {
		if (i < (int)lamps.size()) {
			LoadVector3F(location_lightPosition[i], lamps[i].GetLight().GetPosition());
			LoadVector3F(location_lightColor[i], lamps[i].GetLight().GetColor());
			LoadVector3F(location_attenuation[i], lamps[i].GetLight().GetAttenuation());
		}
		else {
			// If less than MAX_LIGHTS lights are in the lights vector,
			// load up empty information to the shaders.
			glm::vec3 zero(0.0f, 0.0f, 0.0f);
			glm::vec3 unit(1.0f, 0.0f, 0.0f);
			LoadVector3F(location_lightPosition[i], zero);
			LoadVector3F(location_lightColor[i], zero);
			LoadVector3F(location_attenuation[i], unit);
		}
	}
}

void NormalMappingShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(location_projectionMatrix, matrix);
}

void NormalMappingShader::LoadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(camera);
	LoadMatrix4f(location_viewMatrix, viewMatrix);
}

void NormalMappingShader::LoadFakeLightingVariable(const bool& useFakeLighting)
{
	LoadBool(location_useFakeLighting, useFakeLighting);
}

void NormalMappingShader::LoadSkyColor(const float& r, const float& g, const float& b)
{
	LoadVector3F(location_skyColor, glm::vec3(r, g, b));
}

void NormalMappingShader::LoadNumberOfRows(const int& numberOfRows)
{
	LoadFloat(location_numberOfRows, (GLfloat)numberOfRows);
}

void NormalMappingShader::LoadTextureOffset(const float& x, const float& y)
{
	LoadVector2f(location_textureOffset, glm::vec2(x, y));
}

void NormalMappingShader::LoadClipPlane(const glm::vec4& vec)
{
	LoadVector4F(location_clipPlane, vec);
}
