#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Model/BaseModel.hpp"

class Loader
{
public:
	Loader();
	~Loader();

	BaseModel* LoadToVAO(const GLfloat positions[], const int& numberOfVertices);
private:
	GLuint CreateVAOID();
	void LoadDataToAttributeList(const int& attributeNumber, const GLfloat data[], const int& numberOfData);
	void UnbindVAO();

	std::vector<GLuint> m_vaos, m_vbos;
};

#endif // !LOADER_HPP