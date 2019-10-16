#ifndef TEXTMESHCREATOR_HPP
#define TEXTMESHCREATOR_HPP

#include "GUIText.hpp"
#include "TextMeshData.hpp"
#include "MetaFile.hpp"
#include "Line.hpp"

class TextMeshCreator
{
public:
	static constexpr double LINE_HEIGHT = 0.03f;
	static constexpr int SPACE_ASCII = 32;

	TextMeshCreator(std::string metaFile);
	TextMeshData* CreateTextMesh(GUIText* text);
private:
	std::vector<Line*>* CreateStructure(GUIText* text);
	void CompleteStructure(std::vector<Line*>* lines, Line* currentLine, Word* currentWord, GUIText* text);
	TextMeshData* CreateQuadVertices(GUIText* text, std::vector<Line*>* lines);
	void AddVerticesForCharacter(double cursorX, double cursorY, Character character, double fontSize, std::vector<GLfloat>& vertices);
	void AddVertices(std::vector<GLfloat>& vertices, double x, double y, double maxX, double maxY);
	void AddTexCoords(std::vector<GLfloat>& texCoords, double x, double y, double maxX, double maxY);

	MetaFile* m_metaData;
};

#endif // !TEXTMESHCREATOR_HPP