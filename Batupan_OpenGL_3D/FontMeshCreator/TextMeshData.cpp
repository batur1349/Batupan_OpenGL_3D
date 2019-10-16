#include "../pch.h"
#include "TextMeshData.hpp"

TextMeshData::TextMeshData(std::vector<GLfloat> vertexPositions, std::vector<GLfloat> textureCoords)
{
	m_vertexPositions = vertexPositions;
	m_textureCoords = textureCoords;
}

std::vector<GLfloat>& TextMeshData::GetVertexPositions()
{
	return m_vertexPositions;
}

std::vector<GLfloat>& TextMeshData::GetTextureCoords()
{
	return m_textureCoords;
}

int TextMeshData::GetVertexCount()
{
	return m_vertexPositions.size() / 2;
}
