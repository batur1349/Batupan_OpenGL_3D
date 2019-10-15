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

BaseModel Loader::LoadToVAO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals, const std::vector<int>& indices)
{
	// Create the vertex array object's id
	GLuint vaoID = CreateVAOID();

	// Send indices data to the GPU
	int indicesSize = indices.size();
	LoadIndicesToGPU(indices.data(), indicesSize);

	// Load positions data to the attribute list 0
	LoadDataToAttributeList(0, 3, vertices.data(), sizeof(glm::vec3) * vertices.size());

	// Load the texture coordinates data to the attribute list 1
	LoadDataToAttributeList(1, 2, uvs.data(), sizeof(glm::vec2) * uvs.size());

	// Load the normals data to the attribute list 2
	LoadDataToAttributeList(2, 3, normals.data(), sizeof(glm::vec3) * normals.size());

	// Unbind the vertex array object
	UnbindVAO();

	// Return the raw model
	return BaseModel(vaoID, indicesSize);
}

BaseModel Loader::LoadToVAOGui(const std::vector<glm::vec2>& vertices)
{
	GLuint vaoid = CreateVAOID();
	LoadDataToAttributeList(0, 2, vertices.data(), sizeof(glm::vec2) * vertices.size());
	UnbindVAO();

	return BaseModel(vaoid, vertices.size());
}

BaseModel Loader::LoadToVAOSkybox(std::vector<glm::vec3> vertices, int dimension)
{
	// Create the vertex array object's id
	GLuint vaoID = CreateVAOID();
	// Load positions data to the attribute list 0
	LoadDataToAttributeList(0, dimension, vertices.data(), sizeof(glm::vec3) * vertices.size());
	// Unbind the vertex array object
	UnbindVAO();
	// Return the raw model
	return BaseModel(vaoID, vertices.size());
}

BaseModel Loader::LoadToVAONormalMap(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<float>& tangents, std::vector<int>& indices)
{
	GLuint vaoID = CreateVAOID();
	// Send indices data to the GPU
	int indicesSize = indices.size();
	LoadIndicesToGPU(indices.data(), indicesSize);
	StoreDataInAttributeList(0, 3, positions);
	StoreDataInAttributeList(1, 2, textureCoords);
	StoreDataInAttributeList(2, 3, normals);
	StoreDataInAttributeList(3, 3, tangents);
	UnbindVAO();
	return BaseModel(vaoID, indices.size());
}

BaseModel Loader::LoadToVAONormal(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& norm, std::vector<glm::vec3>& tan, std::vector<int>& indices)
{
	// Create the vertex array object's id
	GLuint vaoID = CreateVAOID();

	// Send indices data to the GPU
	int indicesSize = indices.size();
	LoadIndicesToGPU(indices.data(), indicesSize);

	// Load positions data to the attribute list 0
	LoadDataToAttributeList(0, 3, vertices.data(), sizeof(glm::vec3) * vertices.size());

	// Load the texture coordinates data to the attribute list 1
	LoadDataToAttributeList(1, 2, uv.data(), sizeof(glm::vec2) * uv.size());

	// Load the normals data to the attribute list 2
	LoadDataToAttributeList(2, 3, norm.data(), sizeof(glm::vec3) * norm.size());

	LoadDataToAttributeList(3, 3, tan.data(), sizeof(glm::vec3) * tan.size());

	// Unbind the vertex array object
	UnbindVAO();

	// Return the raw model
	return BaseModel(vaoID, indicesSize);
}

GLuint Loader::LoadTexture2D(const std::string& fileName)
{
	GLuint texture;
	int width, height;
	glGenTextures(1, &texture);

	// Load image data
	unsigned char* image;
	image = SOIL_load_image(("../Textures/" + fileName + ".png").c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	if (image == NULL)
	{
		std::cout << "Couldn't load the texture named " << fileName << "\n";
		exit(-1);
	}

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
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.2f);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Return the texture id
	return texture;
}

GLuint Loader::LoadCubeMap(const std::vector<std::string>& fileNames)
{
	GLuint texID;
	glGenTextures(1, &texID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	for (int i = 0; i < fileNames.size(); i++)
	{
		TextureData data = DecodeTextureFile("../Textures/" + fileNames.at(i) + ".png");
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data.GetWidth(), data.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.GetBuffer());
	}


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	m_textures.push_back(texID);
	return texID;
}

GLuint Loader::CreateVAOID()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	m_vaos.push_back(vao);
	glBindVertexArray(vao);
	return vao;
}

void Loader::LoadDataToAttributeList(const int& attribNumber, const int& attribSize, const void* data, const int& dataSize)
{
	GLuint vboID;

	// Create a new vertex buffer object
	glGenBuffers(1, &vboID);

	// Add vertex buffer object to the container
	m_vbos.push_back(vboID);

	// Bind the vertex buffer object to use it
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Load the data to GPU using the vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	// Tell OpenGL how and where to store this VBO in the VAO
	glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::StoreDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
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

void Loader::LoadIndicesToGPU(const int indices[], const int& count)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * count, indices, GL_STATIC_DRAW);
}

TextureData Loader::DecodeTextureFile(const std::string& fileName)
{
	int width = 0, height = 0;
	unsigned char* image = NULL;

	image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	if (image == 0)
	{
		std::cout << "Error :Couldn't load the image." << std::endl;
	}

	return TextureData(image, width, height);
}

void Loader::UnbindVAO()
{
	glBindVertexArray(0);
}