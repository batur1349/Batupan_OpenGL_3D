#ifndef MODELTEXTURE_HPP
#define MODELTEXTURE_HPP

class ModelTexture
{
public:
	ModelTexture(const GLuint& id);

	const GLuint& GetID();
	inline float& GetShineDamper() { return m_shineDamper; }
	inline float& GetReflectivity() { return m_reflectivity; }
	inline bool& GetTransparency() { return m_transparency; }
	inline bool& GetFakeLightning() { return m_fakeLightning; }
	inline int& GetNumberOfRows() { return m_numberOfRows; }

	inline const void SetShineDamper(const float& shineDamper) { m_shineDamper = shineDamper; }
	inline const void SetReflectivity(const float& reflectivity) { m_reflectivity = reflectivity; }
	inline const void SetTransparency(const bool& transparency) { m_transparency = transparency; }
	inline const void SetFakeLightning(const bool& fakeLightning) { m_fakeLightning = fakeLightning; }
	inline const void SetNumberOfRows(const int& numberOfRows) { m_numberOfRows = numberOfRows; }
private:
	GLuint m_textureID;
	int m_numberOfRows = 1;
	float m_shineDamper = 1.0f, m_reflectivity = 0.0f;
	bool m_transparency = false, m_fakeLightning = false;
};

#endif // !MODELTEXTURE_HPP