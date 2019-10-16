#include "../pch.h"
#include "FontType.hpp"

FontType::FontType(GLuint textureAtlas, std::string fontFile)
{
	m_textureAtlas = textureAtlas;
	m_loader = new TextMeshCreator(fontFile);
}

FontType::~FontType()
{
	delete m_loader;
}

GLuint FontType::GetTextureAtlas()
{
	return m_textureAtlas;
}

TextMeshData* FontType::LoadText(GUIText* text)
{
	return m_loader->CreateTextMesh(text);
}
