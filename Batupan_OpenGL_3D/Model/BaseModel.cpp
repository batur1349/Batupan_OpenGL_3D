#include "../pch.h"
#include "BaseModel.hpp"


BaseModel::BaseModel(const GLuint& vaoID, const int& vertexCount)
{
	m_vaoID = vaoID;
	m_vertexCount = vertexCount;
}

const GLuint& BaseModel::GetVaoID()
{
	return m_vaoID;
}

const int& BaseModel::GetVertexCount()
{
	return m_vertexCount;
}
