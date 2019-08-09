#include "../pch.h"
#include "Loader.hpp"


Loader::Loader()
{
	m_vaos.clear();
	m_vbos.clear();
}

Loader::~Loader()
{
	for (int i = 0; i < m_vaos.size(); i++)
		glDeleteVertexArrays(1, &m_vaos.at(i));

	for (int i = 0; i < m_vbos.size(); i++)
		glDeleteBuffers(1, &m_vbos.at(i));
}

BaseModel* Loader::LoadToVAO(const GLfloat positions[], const int& numberOfVertices)
{
	GLuint vaoID = CreateVAOID();
	LoadDataToAttributeList(0, positions, numberOfVertices);
	UnbindVAO();

	return new BaseModel(vaoID, numberOfVertices / 3);
}

GLuint Loader::CreateVAOID()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	m_vaos.push_back(vao);
	glBindVertexArray(vao);
	return vao;
}

void Loader::LoadDataToAttributeList(const int& attributeNumber, const GLfloat data[], const int& numberOfData)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	m_vbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numberOfData * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::UnbindVAO()
{
	glBindVertexArray(0);
}