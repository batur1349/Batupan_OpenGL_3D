#ifndef CHARACTER_HPP
#define CHARACTER_HPP

class Character
{
public:
	Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize, double xOffset, double yOffset,
		double sizeX, double sizeY, double xAdvance);

	inline int GetID() { return m_id; }
	inline double GetXTextureCoordinate() { return m_xTextureCoord; }
	inline double GetYTextureCoordinate() { return m_yTextureCoord; }
	inline double GetXMaxTextureCoord() { return m_xMaxTextureCoord; }
	inline double GetYMaxTextureCoord() { return m_yMaxTextureCoord; }
	inline double GetxOffset() { return m_xOffset; }
	inline double GetyOffset() { return m_yOffset; }
	inline double GetSizeX() { return m_sizeX; }
	inline double GetSizeY() { return m_sizeY; }
	inline double GetxAdvance() { return m_xAdvance; }
private:
	int m_id;
	double m_xTextureCoord;
	double m_yTextureCoord;
	double m_xMaxTextureCoord;
	double m_yMaxTextureCoord;
	double m_xOffset;
	double m_yOffset;
	double m_sizeX;
	double m_sizeY;
	double m_xAdvance;
};

#endif // !CHARACTER_HPP