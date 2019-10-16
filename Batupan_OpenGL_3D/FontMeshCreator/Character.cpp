#include "../pch.h"
#include "Character.hpp"

Character::Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize, double xOffset, double yOffset, double sizeX, double sizeY, double xAdvance)
{
	m_id = id;
	m_xTextureCoord = xTextureCoord;
	m_yTextureCoord = yTextureCoord;
	m_xOffset = xOffset;
	m_yOffset = yOffset;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_xMaxTextureCoord = xTexSize + xTextureCoord;
	m_yMaxTextureCoord = yTexSize + yTextureCoord;
	m_xAdvance = xAdvance;
}
