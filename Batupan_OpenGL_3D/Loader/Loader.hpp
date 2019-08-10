#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Model/BaseModel.hpp"

class Loader
{
public:
	Loader();
	~Loader();

	BaseModel LoadToVAO(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& textureCoordinates, const std::vector<GLuint>& indices);
	GLuint LoadTexture2D(const std::string& fileName);
private:
	GLuint CreateVAOID();
	void LoadDataToAttributeList(const int& attributeNumber, const int& attributeSize, const GLfloat data[], const int& numberOfData);
	void LoadIndicesToGPU(const GLuint indices[], const int& count);
	void UnbindVAO();

	std::vector<GLuint> m_vaos, m_vbos, m_textures;
};

#endif // !LOADER_HPP