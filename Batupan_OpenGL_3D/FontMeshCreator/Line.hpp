#ifndef LINE_HPP
#define LINE_HPP

#include "Word.hpp"

class Line
{
public:
	Line(double spaceWidth, double fontSize, double maxLength);

	bool AttemptToAddWord(Word word);
	double GetMaxLength();
	double GetLineLength();
	std::vector<Word>& GetWords();
private:
	double m_maxLength;
	double m_spaceSize;

	std::vector<Word> m_words;
	double m_currentLineLength = 0;
};

#endif // !LINE_HPP