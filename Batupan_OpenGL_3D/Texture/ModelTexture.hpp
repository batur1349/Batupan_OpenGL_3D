#ifndef MODELTEXTURE_HPP
#define MODELTEXTURE_HPP

class ModelTexture
{
public:
	ModelTexture(const GLuint& id);

	const GLuint& GetID();
private:
	GLuint m_textureID;
};

#endif // !MODELTEXTURE_HPP