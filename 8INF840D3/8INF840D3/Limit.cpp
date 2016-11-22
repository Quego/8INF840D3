#include "stdafx.h"
#include "Limit.h"
#include <iostream>
#include <fstream>
#include <sstream>

Limit::Limit(int alphabetSize, int wordSize) : 
	m_alphabetSize(alphabetSize),
	m_wordSize(wordSize)
{
	std::vector<Occurrence> m_occurrences(alphabetSize);
}

int Limit::getAlphabetSize() const
{
	return m_alphabetSize;
}

int Limit::getWordSize() const
{
	return m_wordSize;
}

std::vector<Occurrence> Limit::getOccurences() const
{
	return m_occurrences;
}

Occurrence Limit::getOccurenceOnWord(int index) const
{
	return m_occurrences[index];;
}

void Limit::AddOccurrence(Occurrence occurrence)
{
	m_occurrences.push_back(occurrence);
}

Limit Limit::Parse(std::string filename)
{
	std::ifstream file(filename, std::ios::in);

	if (file.is_open())
	{
		std::string content;
		int alphabetSize;
		int wordSize;
		std::vector<int> mins;
		std::vector<int> max;

		getline(file, content);
		alphabetSize = std::stoi(content);

		getline(file, content);
		wordSize = std::stoi(content);

		std::string content1;
		std::string content2;
		getline(file, content1);
		getline(file, content2);

		Limit newLimit(alphabetSize, wordSize);
		for (int index = 0; index < alphabetSize; index++)
		{
			std::string minOccurence = content1.substr(0, content1.find(" "));
			std::string maxOccurence = content2.substr(0, content2.find(" "));
			Occurrence occurrence = Occurrence(std::stoi(minOccurence), std::stoi(maxOccurence));
			newLimit.AddOccurrence(occurrence);
			content1.erase(0, minOccurence.size() + 1);
			content2.erase(0, maxOccurence.size() + 1);

		}

		return newLimit;
	}
	else
		throw std::logic_error("Parse : le fichier ne peut être lu");
	return Limit(-1, -1);
}
