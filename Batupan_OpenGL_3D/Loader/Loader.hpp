#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Model/BaseModel.hpp"

class Loader
{
public:
	Loader();
	~Loader();

	BaseModel LoadToVAO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<int>& indices);
	GLuint LoadTexture2D(const std::string& fileName);
private:
	GLuint CreateVAOID();
	void LoadDataToAttributeList(const int& attribNumber, const int& attribSize, const void* data, const int& dataSize);
	void LoadIndicesToGPU(const GLuint indices[], const int& count);
	void LoadIndicesToGPU(const int indices[], const int& count);
	void UnbindVAO();

	std::vector<GLuint> m_vaos, m_vbos, m_textures;
};

#endif // !LOADER_HPP