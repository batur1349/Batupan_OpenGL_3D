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
	inline int& GetNumberOfColumns() { return m_numberOfColumns; }
	inline GLuint& GetNormalMap() { return m_normalMap; }

	inline const void SetShineDamper(const float& shineDamper) { m_shineDamper = shineDamper; }
	inline const void SetReflectivity(const float& reflectivity) { m_reflectivity = reflectivity; }
	inline const void SetTransparency(const bool& transparency) { m_transparency = transparency; }
	inline const void SetFakeLightning(const bool& fakeLightning) { m_fakeLightning = fakeLightning; }
	inline const void SetNumberOfRows(const int& numberOfRows) { m_numberOfRows = numberOfRows; }
	inline const void SetNumberOfColumns(const int& numberOfCols) { m_numberOfColumns = numberOfCols; }
	inline const void SetNormalMap(const GLuint& normalMap) { m_normalMap = normalMap; }
private:
	GLuint m_textureID, m_normalMap;
	int m_numberOfRows = 1, m_numberOfColumns = 1;
	float m_shineDamper = 1.0f, m_reflectivity = 0.0f;
	bool m_transparency = false, m_fakeLightning = false;
};

#endif // !MODELTEXTURE_HPP