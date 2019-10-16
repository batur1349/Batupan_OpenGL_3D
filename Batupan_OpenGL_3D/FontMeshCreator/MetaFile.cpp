#include "../pch.h"
#include "MetaFile.hpp"
#include "TextMeshCreator.hpp"

MetaFile::MetaFile(std::string file)
{
	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

	m_aspectRatio = (double)width / (double)height;
	OpenFile(file);
	LoadPaddingData();
	LoadLineSizes();
	int imageWidth = GetValueOfVariable("scaleW");
	LoadCharacterData(imageWidth);
	Close();
}

Character* MetaFile::GetCharacter(int ascii)
{
	std::map<int, Character*>::iterator it = m_metaData.find(ascii);

	if (it == m_metaData.end())
	{
		return nullptr;
	}

	return it->second;
}

bool MetaFile::ProcessNextLine()
{
	m_values.clear();

	std::string line;
	if (!std::getline(m_ifs, line))
	{
		std::cout << "processNextLine() returned false" << std::endl;
		return false;
	}

	// TODO: this doesn't work right for lines containing e.g.
	// face="Verdana Bold", but it works for my purposes.

	std::istringstream iss(line);
	std::string str;

	while (iss >> str)
	{
		std::stringstream ss(str);
		std::string key, value;
		if (std::getline(ss, key, '='))
		{
			std::getline(ss, value);
			if (key != "" && value != "")
			{
				m_values.insert(std::pair<std::string, std::string>(key, value));
			}
		}
	}

	return true;
}

int MetaFile::GetValueOfVariable(std::string variable)
{
	int result;
	std::map<std::string, std::string>::iterator it = m_values.find(variable);
	if (it == m_values.end())
	{
		return 0;
	}
	std::string value = it->second;
	std::stringstream ss(value);

	if (ss >> result)
	{
		return result;
	}

	return 0;
}

std::vector<int> MetaFile::GetValuesOfVariable(std::string variable)
{
	std::vector<int> result;

	std::map<std::string, std::string>::iterator it = m_values.find(variable);
	if (it == m_values.end())
	{
		return result;
	}
	std::string values = it->second;

	//cout << "Values of variable " << variable << " are " << values << endl;

	// replace commas with space.
	auto x = values.find(",");
	while (x < std::string::npos)
	{
		values.replace(x, 1, " ");
		x = values.find(",", x + 1);
	}

	//cout << "Values of variable " << variable << " are after replace " << values << endl;

	std::istringstream iss(values);

	int number;
	while (iss >> number)
	{
		result.push_back(number);
	}

	return result;
}

void MetaFile::Close()
{
	m_ifs.close();
}

bool MetaFile::OpenFile(std::string file)
{
	m_ifs.open(file, std::ifstream::in);
	if (m_ifs.good())
	{
		//cout << "MetaFile: openFile " << file << " OK" << endl;
		return true;
	}
	else
	{
		std::cerr << "MetaFile: Font meta file " << file << " could not be opened" << std::endl;
		return false;
	}
}

void MetaFile::LoadPaddingData()
{
	ProcessNextLine();
	m_padding = GetValuesOfVariable("padding");

	m_paddingWidth = m_padding[PAD_LEFT] + m_padding[PAD_RIGHT];
	m_paddingHeight = m_padding[PAD_TOP] + m_padding[PAD_BOTTOM];
}

void MetaFile::LoadLineSizes()
{
	ProcessNextLine();

	std::cout << "MetaFile: lineHeight = " << GetValueOfVariable("lineHeight") << std::endl;

	int lineHeightPixels = GetValueOfVariable("lineHeight") - m_paddingHeight;
	m_verticalPerPixelSize = TextMeshCreator::LINE_HEIGHT / (double)lineHeightPixels;
	m_horizontalPerPixelSize = m_verticalPerPixelSize / m_aspectRatio;
}

void MetaFile::LoadCharacterData(int imageWidth)
{
	ProcessNextLine();
	ProcessNextLine();
	int count = 0;
	while (ProcessNextLine())
	{
		Character* c = LoadCharacter(imageWidth);
		if (c != nullptr)
		{
			m_metaData.insert(std::pair<int, Character*>(c->GetID(), c));
		}
		count++;
	}
	//cout << "MetaFile: loaded " << count << " characters" << endl;
}

Character* MetaFile::LoadCharacter(int imageSize)
{
	int id = GetValueOfVariable("id");
	if (id == TextMeshCreator::SPACE_ASCII)
	{
		m_spaceWidth = (GetValueOfVariable("xadvance") - m_paddingWidth) * m_horizontalPerPixelSize;
		return nullptr;
	}
	double xTex = ((double)GetValueOfVariable("x") + (m_padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
	double yTex = ((double)GetValueOfVariable("y") + (m_padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
	int width = GetValueOfVariable("width") - (m_paddingWidth - (2 * DESIRED_PADDING));
	int height = GetValueOfVariable("height") - ((m_paddingHeight)-(2 * DESIRED_PADDING));
	double quadWidth = width * m_horizontalPerPixelSize;
	double quadHeight = height * m_verticalPerPixelSize;
	double xTexSize = (double)width / imageSize;
	double yTexSize = (double)height / imageSize;
	double xOff = (GetValueOfVariable("xoffset") + m_padding[PAD_LEFT] - DESIRED_PADDING) * m_horizontalPerPixelSize;
	double yOff = (GetValueOfVariable("yoffset") + (m_padding[PAD_TOP] - DESIRED_PADDING)) * m_verticalPerPixelSize;
	double xAdvance = (GetValueOfVariable("xadvance") - m_paddingWidth) * m_horizontalPerPixelSize;
	return new Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
}
