#ifndef METAFILE_HPP
#define METAFILE_HPP

#include "Character.hpp"

class MetaFile
{
public:
	MetaFile(std::string file);

	double GetSpaceWidth() { return m_spaceWidth; }
	Character* GetCharacter(int ascii);
private:
	bool ProcessNextLine();
	int GetValueOfVariable(std::string variable);
	std::vector<int> GetValuesOfVariable(std::string variable);
	void Close();
	bool OpenFile(std::string file);
	void LoadPaddingData();
	void LoadLineSizes();
	void LoadCharacterData(int imageWidth);
	Character* LoadCharacter(int imageSize);

	static constexpr int PAD_TOP = 0;
	static constexpr int PAD_LEFT = 1;
	static constexpr int PAD_BOTTOM = 2;
	static constexpr int PAD_RIGHT = 3;

	static constexpr int DESIRED_PADDING = 8;

	std::string SPLITTER = " ";
	std::string NUMBER_SEPARATOR = ",";

	double m_aspectRatio;
	double m_verticalPerPixelSize;
	double m_horizontalPerPixelSize;
	double m_spaceWidth;
	std::vector<int> m_padding;
	int m_paddingWidth;
	int m_paddingHeight;
	std::map<int, Character*> m_metaData;
	std::map<std::string, std::string> m_values;
	std::ifstream m_ifs; // input file
};

#endif // !METAFILE_HPP