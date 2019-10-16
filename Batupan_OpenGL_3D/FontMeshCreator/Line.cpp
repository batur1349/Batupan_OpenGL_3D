#include "../pch.h"
#include "Line.hpp"

Line::Line(double spaceWidth, double fontSize, double maxLength)
{
	m_spaceSize = spaceWidth * fontSize;
	m_maxLength = maxLength;
}

bool Line::AttemptToAddWord(Word word)
{
	double additionalLength = word.GetWordWidth();
	additionalLength += !m_words.empty() ? m_spaceSize : 0;

	if (m_currentLineLength + additionalLength <= m_maxLength)
	{
		m_words.push_back(word);
		m_currentLineLength += additionalLength;
		return true;
	}
	else
	{
		return false;
	}
}

double Line::GetMaxLength()
{
	return m_maxLength;
}

double Line::GetLineLength()
{
	return m_currentLineLength;
}

std::vector<Word>& Line::GetWords()
{
	return m_words;
}
