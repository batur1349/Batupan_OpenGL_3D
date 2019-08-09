#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

class BaseModel
{
public:
	BaseModel(const GLuint& vaoID, const int& vertexCount);

	const GLuint& GetVaoID();
	const int& GetVertexCount();
private:
	GLuint	m_vaoID;
	int		m_vertexCount;
};

#endif // !BASEMODEL_HPP