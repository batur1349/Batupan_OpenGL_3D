#include "../pch.h"
#include "Word.hpp"

Word::Word(double fontSize)
{
	m_fontSize = fontSize;
}

void Word::AddCharacter(Character character)
{
	m_characters.push_back(character);
	m_width += character.GetxAdvance() * m_fontSize;
}

std::vector<Character> Word::GetCharacters()
{
	return m_characters;
}

double Word::GetWordWidth()
{
	return m_width;
}
