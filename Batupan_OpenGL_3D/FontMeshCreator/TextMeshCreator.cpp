#include "../pch.h"
#include "TextMeshCreator.hpp"

TextMeshCreator::TextMeshCreator(std::string metaFile)
{
	m_metaData = new MetaFile(metaFile);
}

TextMeshData* TextMeshCreator::CreateTextMesh(GUIText* text)
{
	std::vector<Line*>* lines = CreateStructure(text);
	TextMeshData* data = CreateQuadVertices(text, lines);

	return data;
}

std::vector<Line*>* TextMeshCreator::CreateStructure(GUIText* text)
{
	std::string chars = text->GetTextString();
	std::cout << "TextMeshCreator::createStructure for \"" << chars << "\"" << std::endl;

	auto lines = new std::vector<Line*>;
	Line* currentLine = new Line(m_metaData->GetSpaceWidth(), text->GetFontSize(), text->GetMaxLineSize());
	Word* currentWord = new Word(text->GetFontSize());

	for (char c : chars)
	{
		int ascii = (int)c;
		if (ascii == SPACE_ASCII)
		{
			bool added = currentLine->AttemptToAddWord(*currentWord);
			if (!added)
			{
				lines->push_back(currentLine);
				currentLine = new Line(m_metaData->GetSpaceWidth(), text->GetFontSize(), text->GetMaxLineSize());
				currentLine->AttemptToAddWord(*currentWord);
			}
			currentWord = new Word(text->GetFontSize());
			continue;
		}
		Character* character = m_metaData->GetCharacter(ascii);
		currentWord->AddCharacter(*character);
	}
	CompleteStructure(lines, currentLine, currentWord, text);
	return lines;
}

void TextMeshCreator::CompleteStructure(std::vector<Line*>* lines, Line* currentLine, Word* currentWord, GUIText* text)
{
	bool added = currentLine->AttemptToAddWord(*currentWord);
	if (!added)
	{
		lines->push_back(currentLine);
		currentLine = new Line(m_metaData->GetSpaceWidth(), text->GetFontSize(), text->GetMaxLineSize());
		currentLine->AttemptToAddWord(*currentWord);
	}
	lines->push_back(currentLine);
}

TextMeshData* TextMeshCreator::CreateQuadVertices(GUIText* text, std::vector<Line*>* lines)
{
	text->SetNumberOfLines(lines->size());
	double cursorX = 0.0;
	double cursorY = 0.0;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> textureCoords;

	for (Line* line : *lines)
	{
		if (text->IsCentered())
		{
			cursorX = (line->GetMaxLength() - line->GetLineLength()) / 2;
		}

		for (Word word : line->GetWords())
		{
			for (Character letter : word.GetCharacters())
			{
				AddVerticesForCharacter(cursorX, cursorY, letter, text->GetFontSize(), vertices);
				AddTexCoords(textureCoords, letter.GetXTextureCoordinate(), letter.GetYTextureCoordinate(), letter.GetXMaxTextureCoord(), letter.GetYMaxTextureCoord());
				cursorX += letter.GetxAdvance() * text->GetFontSize();
			}
			cursorX += m_metaData->GetSpaceWidth() * text->GetFontSize();
		}

		cursorX = 0;
		cursorY += LINE_HEIGHT * text->GetFontSize();
	}

	return new TextMeshData(vertices, textureCoords);
}

void TextMeshCreator::AddVerticesForCharacter(double cursorX, double cursorY, Character character, double fontSize, std::vector<GLfloat>& vertices)
{
	double x = cursorX + (character.GetxOffset() * fontSize);
	double y = cursorY + (character.GetyOffset() * fontSize);
	double maxX = x + (character.GetSizeX() * fontSize);
	double maxY = y + (character.GetSizeY() * fontSize);
	double properX = (2 * x) - 1;
	double properY = (-2 * y) + 1;
	double properMaxX = (2 * maxX) - 1;
	double properMaxY = (-2 * maxY) + 1;
	AddVertices(vertices, properX, properY, properMaxX, properMaxY);
}

void TextMeshCreator::AddVertices(std::vector<GLfloat>& vertices, double x, double y, double maxX, double maxY)
{
	vertices.push_back((GLfloat)x);
	vertices.push_back((GLfloat)y);
	vertices.push_back((GLfloat)x);
	vertices.push_back((GLfloat)maxY);
	vertices.push_back((GLfloat)maxX);
	vertices.push_back((GLfloat)maxY);
	vertices.push_back((GLfloat)maxX);
	vertices.push_back((GLfloat)maxY);
	vertices.push_back((GLfloat)maxX);
	vertices.push_back((GLfloat)y);
	vertices.push_back((GLfloat)x);
	vertices.push_back((GLfloat)y);
}

void TextMeshCreator::AddTexCoords(std::vector<GLfloat>& texCoords, double x, double y, double maxX, double maxY)
{
	texCoords.push_back((GLfloat)x);
	texCoords.push_back((GLfloat)y);
	texCoords.push_back((GLfloat)x);
	texCoords.push_back((GLfloat)maxY);
	texCoords.push_back((GLfloat)maxX);
	texCoords.push_back((GLfloat)maxY);
	texCoords.push_back((GLfloat)maxX);
	texCoords.push_back((GLfloat)maxY);
	texCoords.push_back((GLfloat)maxX);
	texCoords.push_back((GLfloat)y);
	texCoords.push_back((GLfloat)x);
	texCoords.push_back((GLfloat)y);
}
