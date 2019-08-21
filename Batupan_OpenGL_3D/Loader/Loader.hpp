#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Model/BaseModel.hpp"
#include "../Texture/TextureData.hpp"

class Loader
{
public:
	Loader();
	~Loader();

	BaseModel LoadToVAO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals, const std::vector<int>& indices);
	BaseModel LoadToVAOGui(const std::vector<glm::vec2>& vertices);
	BaseModel LoadToVAOSkybox(std::vector<glm::vec3> vertices, int dimension);
	GLuint LoadTexture2D(const std::string& fileName);
	GLuint LoadCubeMap(const std::vector<std::string>& fileNames);
private:
	GLuint CreateVAOID();
	void LoadDataToAttributeList(const int& attribNumber, const int& attribSize, const void* data, const int& dataSize);
	void LoadIndicesToGPU(const GLuint indices[], const int& count);
	void LoadIndicesToGPU(const int indices[], const int& count);
	TextureData DecodeTextureFile(const std::string& fileName);
	void UnbindVAO();

	std::vector<GLuint> m_vaos, m_vbos, m_textures;
};

#endif // !LOADER_HPP