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

BaseModel* Loader::LoadToVAO(const std::vector<GLfloat>& positions, const std::vector<GLuint>& indices)
{
	GLuint vaoID = CreateVAOID();
	LoadDataToAttributeList(0, positions.data(), positions.size());
	LoadIndicesToGPU(indices.data(), indices.size());
	UnbindVAO();

	return new BaseModel(vaoID, indices.size());
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

void Loader::LoadIndicesToGPU(const GLuint indices[], const int& count)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * count, indices, GL_STATIC_DRAW);
}

void Loader::UnbindVAO()
{
	glBindVertexArray(0);
}