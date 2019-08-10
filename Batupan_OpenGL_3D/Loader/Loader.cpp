#include "../pch.h"
#include "Loader.hpp"


Loader::Loader()
{
	m_vaos.clear();
	m_vbos.clear();
	m_textures.clear();
}

Loader::~Loader()
{
	for (int i = 0; i < m_vaos.size(); i++)
		glDeleteVertexArrays(1, &m_vaos.at(i));

	for (int i = 0; i < m_vbos.size(); i++)
		glDeleteBuffers(1, &m_vbos.at(i));

	for (int i = 0; i < m_textures.size(); i++)
		glDeleteBuffers(1, &m_textures.at(i));
}

BaseModel Loader::LoadToVAO(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& textureCoordinates, const std::vector<GLuint>& indices)
{
	GLuint vaoID = CreateVAOID();
	LoadDataToAttributeList(0, 3, positions.data(), positions.size());
	LoadDataToAttributeList(1, 2, textureCoordinates.data(), textureCoordinates.size());
	LoadIndicesToGPU(indices.data(), indices.size());
	UnbindVAO();

	return BaseModel(vaoID, indices.size());
}

GLuint Loader::LoadTexture2D(const std::string& fileName)
{
	GLuint texture;
	int width, height;
	glGenTextures(1, &texture);

	// Load image data
	unsigned char* image;
	image = SOIL_load_image(("../Textures/" + fileName + ".png").c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	// Bind the texture data
	glBindTexture(GL_TEXTURE_2D, texture);

	// Texture the loaded 2D image data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Add the image to the textures container
	m_textures.push_back(texture);

	// Clean-up the image data
	SOIL_free_image_data(image);

	// Generate the mipmap texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// If value is became lower than quality will be high
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Return the texture id
	return texture;
}

GLuint Loader::CreateVAOID()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	m_vaos.push_back(vao);
	glBindVertexArray(vao);
	return vao;
}

void Loader::LoadDataToAttributeList(const int& attributeNumber, const int& attributeSize, const GLfloat data[], const int& numberOfData)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	m_vbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numberOfData * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, attributeSize, GL_FLOAT, GL_FALSE, 0, nullptr);
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