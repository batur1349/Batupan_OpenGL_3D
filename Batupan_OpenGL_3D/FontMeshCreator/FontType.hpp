#ifndef FONTTYPE_HPP
#define FONTTYPE_HPP

#include "TextMeshData.hpp"
#include "TextMeshCreator.hpp"

class FontType
{
public:
	FontType(GLuint textureAtlas, std::string fontFile);
	~FontType();
	GLuint GetTextureAtlas();
	TextMeshData* LoadText(GUIText* text);
private:
	GLuint m_textureAtlas;
	TextMeshCreator* m_loader;
};

#endif // !FONTTYPE_HPP