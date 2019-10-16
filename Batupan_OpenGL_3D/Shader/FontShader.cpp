#include "../pch.h"
#include "FontShader.hpp"


FontShader::FontShader()
	: ShaderProgram(FONT_SHADER_FILE)
{
	BindAttributes();
	GetAllUniformLocations();
}

void FontShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoords");
}

void FontShader::GetAllUniformLocations()
{
	m_location_color = GetUniformLocation("color");
	m_location_translation = GetUniformLocation("translation");
}

void FontShader::LoadColor(glm::vec3 color)
{
	LoadVector3F(m_location_color, color);
}

void FontShader::LoadTranslation(glm::vec2 translation)
{
	LoadVector2f(m_location_translation, translation);
}
