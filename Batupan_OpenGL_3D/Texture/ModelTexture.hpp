#ifndef MODELTEXTURE_HPP
#define MODELTEXTURE_HPP

class ModelTexture
{
public:
	ModelTexture(const GLuint& id);

	const GLuint& GetID();
	inline float& GetShineDamper() { return m_shineDamper; }
	inline float& GetReflectivity() { return m_reflectivity; }

	inline const void SetShineDamper(const float& shineDamper) { m_shineDamper = shineDamper; }
	inline const void SetReflectivity(const float& reflectivity) { m_reflectivity = reflectivity; }
private:
	GLuint m_textureID;
	float m_shineDamper = 1.0f, m_reflectivity = 0.0f;
};

#endif // !MODELTEXTURE_HPP