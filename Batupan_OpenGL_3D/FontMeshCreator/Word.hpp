#ifndef WORD_HPP
#define WORD_HPP

#include "Character.hpp"

class Word
{
public:
	Word(double fontSize);

	void AddCharacter(Character character);
	std::vector<Character> GetCharacters();
	double GetWordWidth();
private:
	std::vector<Character> m_characters;
	double m_width = 0;
	double m_fontSize;
};

#endif // !WORD_HPP