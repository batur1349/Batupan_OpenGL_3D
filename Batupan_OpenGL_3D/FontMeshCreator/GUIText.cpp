#include "../pch.h"
#include "GUIText.hpp"
#include "TextMaster.hpp"

GUIText::GUIText(std::string text, GLfloat fontSize, FontType* font, glm::vec2 position, GLfloat maxLineLength, bool centered)
{
	m_textString = text;
	m_fontSize = fontSize;
	m_font = font;
	m_position = position;
	m_lineMaxSize = maxLineLength;
	m_centerText = centered;

	m_textMaster.LoadText(this);
}

void GUIText::Remove()
{
	m_textMaster.RemoveText(this);
}

FontType* GUIText::GetFont()
{
	return m_font;
}

glm::vec3 GUIText::GetColor()
{
	return m_color;
}

void GUIText::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	m_color = glm::vec3(r, g, b);
}

int GUIText::GetNumberOfLines()
{
	return m_numberOfLines;
}

glm::vec2 GUIText::GetPosition()
{
	return m_position;
}

GLuint GUIText::GetMesh()
{
	return m_textMeshVao;
}

void GUIText::SetMeshInfo(GLuint vao, int verticesCount)
{
	m_textMeshVao = vao;
	m_vertexCount = verticesCount;
}

int GUIText::GetVertexCount()
{
	return m_vertexCount;
}

int GUIText::GetFontSize()
{
	return m_fontSize;
}

void GUIText::SetNumberOfLines(int number)
{
	m_numberOfLines = number;
}

bool GUIText::IsCentered()
{
	return m_centerText;
}

GLfloat GUIText::GetMaxLineSize()
{
	return m_lineMaxSize;
}

std::string GUIText::GetTextString()
{
	return m_textString;
}
