#ifndef TEXTMESHDATA_HPP
#define TEXTMESHDATA_HPP

class TextMeshData
{
public:
	TextMeshData(std::vector<GLfloat> vertexPositions, std::vector<GLfloat> textureCoords);

	std::vector<GLfloat>& GetVertexPositions();
	std::vector<GLfloat>& GetTextureCoords();
	int GetVertexCount();
private:
	std::vector<GLfloat> m_vertexPositions;
	std::vector<GLfloat> m_textureCoords;
};

#endif // !TEXTMESHDATA_HPP