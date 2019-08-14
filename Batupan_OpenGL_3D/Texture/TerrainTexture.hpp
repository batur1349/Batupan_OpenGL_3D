#ifndef TERRAINTEXTURE_HPP
#define TERRAINTEXTURE_HPP

class TerrainTexture
{
public:
	TerrainTexture(const GLuint& textureID);

	inline GLuint& GetTextureID() { return m_textureID; }
private:
	GLuint m_textureID;
};

#endif // !TERRAINTEXTURE_HPP