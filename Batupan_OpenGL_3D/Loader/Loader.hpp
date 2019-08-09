#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Model/BaseModel.hpp"

class Loader
{
public:
	Loader();
	~Loader();

	BaseModel* LoadToVAO(const std::vector<GLfloat>& positions, const std::vector<GLuint>& indices);
private:
	GLuint CreateVAOID();
	void LoadDataToAttributeList(const int& attributeNumber, const GLfloat data[], const int& numberOfData);
	void LoadIndicesToGPU(const GLuint indices[], const int& count);
	void UnbindVAO();

	std::vector<GLuint> m_vaos, m_vbos;
};

#endif // !LOADER_HPP