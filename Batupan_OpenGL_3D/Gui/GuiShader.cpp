#include "../pch.h"
#include "GuiShader.hpp"


GuiShader::GuiShader()
	: ShaderProgram(GUI_SHADER_FILE)
{
	BindAttributes();
	GetAllUniformLocations();
}

const void GuiShader::LoadTransformationMatrix(const glm::mat4& matrix)
{
	LoadMatrix4f(m_location_transformationMatrix, matrix);
}

void GuiShader::BindAttributes()
{
	BindAttribute(0, "position");
}

void GuiShader::GetAllUniformLocations()
{
	m_location_transformationMatrix = GetUniformLocation("transformationMatrix");
}
