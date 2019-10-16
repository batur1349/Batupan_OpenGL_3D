#ifndef GUITEXT_HPP
#define GUITEXT_HPP

class FontType;

class GUIText
{
public:
	GUIText(std::string text, GLfloat fontSize, FontType* font, glm::vec2 position, GLfloat maxLineLength, bool centered);

	void Remove();
	FontType* GetFont();
	glm::vec3 GetColor();
	void SetColor(GLfloat r, GLfloat g, GLfloat b);
	int GetNumberOfLines();
	glm::vec2 GetPosition();
	GLuint GetMesh();
	void SetMeshInfo(GLuint vao, int verticesCount);
	int GetVertexCount();
	int GetFontSize();
	void SetNumberOfLines(int number);
	bool IsCentered();
	GLfloat GetMaxLineSize();
	std::string GetTextString();
private:
	std::string m_textString;
	GLfloat m_fontSize;
	GLuint m_textMeshVao;
	int m_vertexCount;
	glm::vec3 m_color = glm::vec3(0, 0, 0);
	glm::vec2 m_position;
	GLfloat m_lineMaxSize;
	int m_numberOfLines;

	FontType* m_font;

	bool m_centerText = false;
};

#endif // !GUITEXT_HPP